// import capifClient from '../../lib/openapi/webui/js/index.js';
const capifWebUiClient = require('capif-webui-client');
const { ApiClient, DefaultApi, ServiceAPIDescription } = capifWebUiClient;
// import ApiClient from '../../lib/openapi/webui/js/src/ApiClient';
// import DefaultApi from '../../lib/openapi/webui/js/src/api/DefaultApi';

const my_api_client = new ApiClient("http://127.0.0.1:8080");
const my_default_api = new DefaultApi(my_api_client);

var callback = function (error, data, response) {
    if (error) {
        console.error(error);
    } else {
        console.log('API called successfully. Returned data: ');
        console.log(JSON.stringify(data, null, 2));
    }
};

let serviceAPIDescription = {
    apiName: "TestAPI",
    aefProfiles: [
        {
            aefId: "Test AEF",
            versions: [
                { apiVersion: "v1" }
            ],
            domainName: "localhost"
        }
    ]
};


//my_default_api.serviceApisV1AllServiceAPIsGet("123", callback);
my_default_api.publishedApisV1ApfIdServiceApisPost("002", serviceAPIDescription, callback);
my_default_api.publishedApisV1ApfIdServiceApisGet("002", callback);