#include "GNG/rest_client.hpp"


namespace GNG {

RestClient::RestClient(const QString &token,
                       const QString &apiURL) noexcept
                       : IRestClient(token, apiURL){}

}
