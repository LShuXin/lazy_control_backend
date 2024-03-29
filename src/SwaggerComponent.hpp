#ifndef SWAGGER_COMPONENT_HPP
#define SWAGGER_COMPONENT_HPP

#include "oatpp-swagger/Model.hpp"
#include "oatpp-swagger/Resources.hpp"
#include "oatpp/core/macro/component.hpp"

/**
 *  Swagger ui is served at
 *  http://host:port/swagger/ui
 */
class SwaggerComponent {
public:

    /**
     *  General API docs info
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, swaggerDocumentInfo)([] {

        oatpp::swagger::DocumentInfo::Builder builder;

        builder
            .setTitle("Lazy Control Api Document")
            .setDescription("API 文档")
            .setVersion("1.0")
            .setContactName("liu shuxin")
            .setContactUrl("https://www.bt.com")

            .setLicenseName("Apache License, Version 2.0")
            .setLicenseUrl("http://www.apache.org/licenses/LICENSE-2.0")

            .addServer("http://localhost:8000", "Apple");

        return builder.build();

    }());


    /**
     *  Swagger-Ui Resources (<oatpp-examples>/lib/oatpp-swagger/res)
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, swaggerResources)([] {
        // Make sure to specify correct full path to oatpp-swagger/res folder !!!
        return oatpp::swagger::Resources::loadResources(OATPP_SWAGGER_RES_PATH);
    }());

};

#endif /* SwaggerComponent_hpp */
