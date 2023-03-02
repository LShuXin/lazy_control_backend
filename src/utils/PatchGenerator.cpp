#include "utils/DiffMatchPatch.hpp"
#include <cstring>
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;


struct wastring : wstring  // The same as wstring, but can be constructed from char* (to use ASCII strings in the test functions)
{
    wastring() {}
    wastring(const wstring& s) : wstring(s) {}
    wastring(const value_type* s) : wstring(s) {}
    wastring(const value_type* s, size_t n) : wstring(s, n) {}
    wastring(const char* s) : wstring(s, s + strlen(s)) {}
    wastring(const char* s, size_t n) : wstring(s, s + n) {}
    wastring operator+=(value_type c) { append(1, c); return *this; }
    wastring operator+=(const wastring& s) { append(s); return *this; }
    wastring operator+=(const char* s) { append(s, s + strlen(s)); return *this; }

    static const wchar_t eol = L'\n';
    static const wchar_t tab = L'\t';
};

inline wastring operator+(const wastring& s, const char* p) { return s + wastring(p); }
inline wastring operator+(const char* p, const wastring& s) { return wastring(p) + s; }

ostream& operator<<(ostream& o, const wastring& s)
{
    o << setfill('0');
    for (wastring::const_pointer p = s.c_str(), end = p + s.length(); p != end; ++p)
    {
        if (*p >= 0x80)
            o << "\\u" << hex << setw(4) << unsigned(*p);
        else if (*p >= ' ')
            o << char(*p);
        else
            switch (char(*p)) {
                case '\n': o << "\\n"; break;
                case '\r': o << "\\r"; break;
                case '\t': o << "\\t"; break;
                default: o << "\\x" << hex << setw(2) << unsigned(*p);
            }
    }
    return o;
}



#define dmp (*this)
class PatchGenerator : diff_match_patch<string> {
typedef vector<string_t> Strings;
typedef diff_match_patch_traits<char> traits;

public:
    /// 生成补丁字符串
    string_t generatePatch(string_t base_text, string_t full_text) {
        dmp.Match_Distance = 1000;
        dmp.Match_Threshold = 0.5f;
        dmp.Patch_DeleteThreshold = 0.5f;

        // 生成补丁
        Patches patches = dmp.patch_make(base_text, full_text);
        // 测试补丁应用效果
        // pair<string_t, vector<bool> > results = dmp.patch_apply(patches, base_text);
        // cout << results.first << endl;

        // 将补丁转为字符串返回
        return dmp.patch_toText(patches);

    }
private:
    // Define equality.
    void assertEquals(const char* strCase, int n1, int n2) {
        if (n1 != n2) {
            cerr << strCase << " FAIL\nExpected: " << n1 << "\nActual: " << n2 << endl;
            throw strCase;
        }
        cout << strCase << " OK" << endl;
    }

    void assertEquals(const char* strCase, const string_t &s1, const string_t &s2) {
        if (s1 != s2) {
            cerr << strCase << " FAIL\nExpected: " << s1 << "\nActual: " << s2 << endl;
            throw strCase;
        }
        cout << strCase << " OK" << endl;
    }

    void assertEquals(const char* strCase, const Diff &d1, const Diff &d2) {
        if (d1 != d2) {
            cerr << strCase << " FAIL\nExpected: " << d1.toString() << "\nActual: " << d2.toString() << endl;
            throw strCase;
        }
        cout << strCase << " OK" << endl;
    }

    void assertEquals(const char* strCase, const Diffs &list1, const Diffs &list2) {
        bool fail = false;
        if (list1.size() == list2.size()) {
            for (Diffs::const_iterator d1 = list1.begin(), d2 = list2.begin(); d1 != list1.end(); ++d1, ++d2) {
                if (*d1 != *d2) {
                    fail = true;
                    break;
                }
            }
        } else {
            fail = true;
        }

        if (fail) {
            // Build human readable description of both lists.
            string_t listString1 = "(";
            bool first = true;
            for (Diffs::const_iterator d1 = list1.begin(); d1 != list1.end(); ++d1) {
                if (!first) {
                    listString1 += ", ";
                }
                listString1 += (*d1).toString();
                first = false;
            }
            listString1 += ")";
            string_t listString2 = "(";
            first = true;
            for (Diffs::const_iterator d2 = list2.begin(); d2 != list2.end(); ++d2) {
                if (!first) {
                    listString2 += ", ";
                }
                listString2 += (*d2).toString();
                first = false;
            }
            listString2 += ")";
            cerr << strCase << " FAIL\nExpected: " << listString1 << "\nActual: " << listString2 << endl;
            throw strCase;
        }
        cout << strCase << " OK" << endl;
    }

    void assertEquals(const char* strCase, const string_t& text1_1, const string_t& text2_1, const Lines &lines1,
                      const string_t& text1_2, const string_t& text2_2, const Lines &lines2)
    {
        bool fail = false;
        if (text1_1 != text1_2 || text2_1 != text2_2 || lines1.size() != lines2.size())
            fail = true;
        else
            for (Lines::const_iterator i = lines1.begin(), j = lines2.begin(); i != lines1.end(); ++i, ++j)
                if (string_t((*i).first, (*i).second) != string_t((*j).first, (*j).second)) { fail = true; break; }

        if (fail) {
            // Build human readable description of both lists.
            string_t listString1 = "\"" + text1_1 + "\", \"" + text2_1 + "\", (\"";
            bool first = true;
            for (Lines::const_iterator i = lines1.begin() + 1; i != lines1.end(); ++i) {
                if (!first) listString1 += "\", \"";
                listString1.append((*i).first, (*i).second);
                first = false;
            }
            listString1 += "\")";
            string_t listString2 = "\"" + text1_2 + "\", \"" + text2_2 + "\", (\"";
            first = true;
            for (Lines::const_iterator j = lines2.begin() + 1; j != lines2.end(); ++j) {
                if (!first) listString2 += "\", \"";
                listString2.append((*j).first, (*j).second);
                first = false;
            }
            listString2 += "\")";
            cerr << strCase << " FAIL\nExpected: " << listString1 << "\nActual: " << listString2 << endl;
            throw strCase;
        }
        cout << strCase << " OK" << endl;
    }

    void assertEquals(const char* strCase, const map<char_t, int> &m1, const map<char_t, int> &m2) {
        map<char_t, int>::const_iterator i1 = m1.begin(), i2 = m2.begin();

        while (i1 != m1.end() && i2 != m2.end()) {
            if ((*i1).first != (*i2).first || (*i1).second != (*i2).second) {
                cerr << strCase << " FAIL\nExpected: (" << char((*i1).first) << ", " << (*i1).second <<
                     ")\nActual: (" << char((*i2).first) << ", " << (*i2).second << ')' << endl;
                throw strCase;
            }
            ++i1, ++i2;
        }

        if (i1 != m1.end()) {
            cerr << strCase << " FAIL\nExpected: (" << char((*i1).first) << ", " << (*i1).second << ")\nActual: none" << endl;
            throw strCase;
        }
        if (i2 != m2.end()) {
            cerr << strCase << " FAIL\nExpected: none\nActual: (" << char((*i2).first) << ", " << (*i2).second << ')' << endl;
            throw strCase;
        }
        cout << strCase << " OK" << endl;
    }

    void assertEquals(const char* strCase, const Strings &list1, const Strings &list2) {
        if (list1 != list2) {
            cerr << strCase << " FAIL\nExpected: " << join(list1, ',') << "\nActual: " << join(list2, ',') << endl;
            throw strCase;
        }
        cout << strCase << " OK" << endl;
    }

    void assertTrue(const char* strCase, bool value) {
        if (!value) {
            cerr << strCase << " FAIL\nExpected: true\nActual: false" << endl;
            throw strCase;
        }
        cout << strCase << " OK" << endl;
    }

    void assertFalse(const char* strCase, bool value) {
        if (value) {
            cerr << strCase << " FAIL\nExpected: false\nActual: true" << endl;
            throw strCase;
        }
        cout << strCase << " OK" << endl;
    }

    void assertEmpty(const char* strCase, const Strings &list) {
        if (!list.empty()) {
            throw strCase;
        }
    }

    // Construct the two texts which made up the diff originally.
    static Strings diff_rebuildtexts(Diffs diffs) {
        Strings text;
        text.push_back(string_t());
        text.push_back(string_t());
        Strings::iterator t1 = text.begin(), t0 = t1++;
        for (Diffs::const_iterator myDiff = diffs.begin(); myDiff != diffs.end(); ++myDiff) {
            if ((*myDiff).operation != INSERT) {
                *t0 += (*myDiff).text;
            }
            if ((*myDiff).operation != DELETE) {
                *t1 += (*myDiff).text;
            }
        }
        return text;
    }

    // Private function for quickly building lists of diffs.
    static Diffs diffList(
            // Diff(INSERT, NULL) is invalid and thus is used as the default argument.
            Diff d1 = Diff(INSERT, string_t()), Diff d2 = Diff(INSERT, string_t()),
            Diff d3 = Diff(INSERT, string_t()), Diff d4 = Diff(INSERT, string_t()),
            Diff d5 = Diff(INSERT, string_t()), Diff d6 = Diff(INSERT, string_t()),
            Diff d7 = Diff(INSERT, string_t()), Diff d8 = Diff(INSERT, string_t()),
            Diff d9 = Diff(INSERT, string_t()), Diff d10 = Diff(INSERT, string_t())) {
        // Diff(INSERT, NULL) is invalid and thus is used as the default argument.
        Diffs listRet;
        if (d1.operation == INSERT && d1.text.empty()) {
            return listRet;
        }
        listRet.push_back(d1);

        if (d2.operation == INSERT && d2.text.empty()) {
            return listRet;
        }
        listRet.push_back(d2);

        if (d3.operation == INSERT && d3.text.empty()) {
            return listRet;
        }
        listRet.push_back(d3);

        if (d4.operation == INSERT && d4.text.empty()) {
            return listRet;
        }
        listRet.push_back(d4);

        if (d5.operation == INSERT && d5.text.empty()) {
            return listRet;
        }
        listRet.push_back(d5);

        if (d6.operation == INSERT && d6.text.empty()) {
            return listRet;
        }
        listRet.push_back(d6);

        if (d7.operation == INSERT && d7.text.empty()) {
            return listRet;
        }
        listRet.push_back(d7);

        if (d8.operation == INSERT && d8.text.empty()) {
            return listRet;
        }
        listRet.push_back(d8);

        if (d9.operation == INSERT && d9.text.empty()) {
            return listRet;
        }
        listRet.push_back(d9);

        if (d10.operation == INSERT && d10.text.empty()) {
            return listRet;
        }
        listRet.push_back(d10);

        return listRet;
    }

    Strings diff_halfMatch(const string_t &text1, const string_t &text2) {
        Strings list;
        HalfMatchResult hm;
        if (diff_match_patch<string>::diff_halfMatch(text1, text2, hm)) {
            list.push_back(hm.text1_a);
            list.push_back(hm.text1_b);
            list.push_back(hm.text2_a);
            list.push_back(hm.text2_b);
            list.push_back(hm.mid_common);
        }
        return list;
    }

    static string_t join(const Strings &list, char delim) {
        string_t s;
        for (Strings::const_iterator i = list.begin(); i != list.end(); ++i) {
            if (i != list.begin()) s += delim;
            s += *i;
        }
        return s;
    }

    static Strings split(const string_t& str, char delim) {
        Strings list;
        string_t::size_type token_len;
        for (string_t::const_pointer token = str.c_str(), end = token + str.length(), p; token < end; token += token_len + 1) {
            for (p = token; p != end; ++p) if (*p == delim) break;
            list.push_back(string_t(token, token_len = p - token));
        }
        return list;
    }
};