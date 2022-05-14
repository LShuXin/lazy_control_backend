#ifndef LoginController_hpp
#define LoginController_hpp

#include "dto/auth/AuthDTOs.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- Begin codegen

/**
 * Sample Api Controller.
 */
class LoginController : public oatpp::web::server::api::ApiController {
private:
  typedef LoginController __ControllerType;
public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize DTOs.
   */
  LoginController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
public:
  
  ENDPOINT_ASYNC("GET", "/login", Root) {
    
    ENDPOINT_ASYNC_INIT(Root)
    
    Action act() override {
      auto dto = LoginResponseDto::createShared();
      dto->statusCode = 200;
      dto->data = "thisistoken";
      dto->message = "ok";
      return _return(controller->createDtoResponse(Status::CODE_200, dto));
    }
    
  };
  
  // TODO Insert Your endpoints here !!!
  
};

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- End codegen

#endif /* LoginController_hpp */
