#ifndef RESTCLIENT_H
#define RESTCLIENT_H

#include "i_rest_client.hpp"
#include "rest_domain.hpp"

namespace GNG {

class RestClient : public IRestClient{

public:
    RestClient(const QString& token,
               const QString& apiURL = RestApiURL) noexcept;
};

}
#endif // RESTCLIENT_H
