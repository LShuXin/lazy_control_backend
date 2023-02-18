-- INSERT INTO AppConfigDetail (
--     config_id,
--     config_name,
--     content,
--     config_version,
--     create_uid,
--     create_stamp
-- )
-- VALUES
-- (
--     1,
--     "lazy_control",
--     "{}",
--     2,
--     0,
--     1660062483895
-- );

-- SELECT COUNT(*) FROM AppConfigItem;

SELECT MAX(config_version)
FROM AppConfigDetail
WHERE config_id=0