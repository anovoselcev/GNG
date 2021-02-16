#ifndef RESTCLIENT_H
#define RESTCLIENT_H

#include "i_rest_client.h"
#include "rest_domain.hpp"

namespace GNG {

class RestClient : public IRestClient
{
    Q_OBJECT
public:
    RestClient(const QString& token,
               const QString& apiURL = RestApiURL) noexcept;
};

}
#endif // RESTCLIENT_H
