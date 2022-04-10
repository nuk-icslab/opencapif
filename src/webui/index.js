// import capifClient from '../../lib/openapi/webui/js/index.js';
const capifWebUiClient = require('capif-webui-client');
const { ApiClient, DefaultApi } = capifWebUiClient;
// import ApiClient from '../../lib/openapi/webui/js/src/ApiClient';
// import DefaultApi from '../../lib/openapi/webui/js/src/api/DefaultApi';

const my_api_client = new ApiClient("http://127.0.0.1:8080");
const my_default_api = new DefaultApi(my_api_client);

my_default_api.serviceApisV1AllServiceAPIsGet("123", (error, data, response) => {
    console.log(error, data, response)
});