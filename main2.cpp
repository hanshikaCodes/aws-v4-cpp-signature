#include <iostream>
#include <curlpp/Options.hpp>
#include "awsv4.hpp"
using namespace std;
int main() {

    // current time
    struct std::tm *t;
    time_t rawtime;
    time( &rawtime );
    t = localtime( &rawtime );
    const std::time_t request_date = std::mktime(t);
    cout<<"request date : "<<request_date;
    

    const std::string region{"us-east-1"};
    const std::string service{"iam"};
    const std::string base_uri{"https://iam.amazonaws.com"};
    const std::string query_args{""};
    const std::string uri_str{base_uri + "?" + query_args};

    Poco::URI uri;
    try {
        uri = Poco::URI("/");
    } catch (std::exception& e) {
        throw std::runtime_error(e.what());
    }
    uri.normalize();


    const auto canonical_uri = AWSV4::canonicalize_uri(uri);    
    const auto canonical_query = AWSV4::canonicalize_query(uri);
    const std::vector<std::string> headers{"host: iam.amazonaws.com"};
    
    const auto canonical_headers_map = AWSV4::canonicalize_headers(headers);
    if (canonical_headers_map.empty()) {
        std::cerr << "headers malformed" << std::endl;
        std::exit(1);
    }
    const auto headers_string = AWSV4::map_headers_string(canonical_headers_map);
     const string signed_headers = "host";
     const std::string payload{""};
     auto sha256_payload = AWSV4::sha256_base16(payload); 
     auto credential_scope = AWSV4::credential_scope(request_date,region,service,"%2F");
     auto credential_scope_n = AWSV4::credential_scope(request_date,region,service,"/");
     cout<<"\n kindly put your credentials and remove this getchar line in line 46, incomplete output without credentials"<<endl;
     getchar();
     string access_key = "put your key";
     string secret_key = "put your secret key";
     std::string canonical_querystring ="Action=CreateUser&UserName=NewUser02&Version=2010-05-08";
     canonical_querystring += "&X-Amz-Algorithm=AWS4-HMAC-SHA256";
     canonical_querystring += "&X-Amz-Credential=" +access_key + "%2F" +(std::string)credential_scope;
    
    std::string amz_date = AWSV4::ISO8601_date(request_date);
    canonical_querystring += "&X-Amz-Date=" + amz_date;
    canonical_querystring += "&X-Amz-Expires=30";
    canonical_querystring += "&X-Amz-SignedHeaders=host";
    const auto canonical_request = AWSV4::canonicalize_request(AWSV4::POST,
                                                               canonical_uri,
                                                               canonical_querystring,
                                                               headers_string,                                                               signed_headers,
                                                               payload);
    
    std::cout << "--\n" << canonical_request << "\n--\n" << std::endl;

    auto hashed_canonical_request = AWSV4::sha256_base16(canonical_request); 
    std::cout << hashed_canonical_request << std::endl;

    auto string_to_sign = AWSV4::string_to_sign(AWSV4::STRING_TO_SIGN_ALGO,
                                                request_date,
                                                credential_scope_n,
                                                hashed_canonical_request);

    std::cout << "--\n" << string_to_sign << "\n----\n" << std::endl;

   
    auto signature = AWSV4::calculate_signature(request_date, 
                                                secret_key,
                                                region,
                                                service,
                                                string_to_sign);
    
    std::cout << "signature :\n"<< signature << std::endl;
    canonical_querystring+="&X-Amz-Signature="+(std::string)signature;

    string request_url = base_uri + "?" + canonical_querystring;
    std::ostringstream os;
    os<< curlpp::options::Url(request_url);
    std::string asAskedInQuestion = os.str();
    std::cout<< asAskedInQuestion;
    return 0;
}
