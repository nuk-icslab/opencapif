const capifApfClient = require('capif-aef-client');
const { ccfUrl } = require('./config');
const { ApiClient, DefaultApi, InvocationLog, Log } = capifApfClient;

const my_api_client = new ApiClient(ccfUrl);
const my_default_api = new DefaultApi(my_api_client);

// Express middleware
function capifAef(aefId, apiId = "0000") {
    return (req, res, next) => {
        let callback = (error, data, response) => {
            if (error) {
                console.error("[CAPIF][AEF] Error occurs while logging")
                console.error(error);
            }
        };
        let url = req.originalUrl.split('/');
        let apiName = url[0];
        let apiVersion = url[1];
        let resourceName = url.slice(2).join('/');
        let protocol = "1_1";
        let operation = req.method;
        let result = "200";
        let apiInvokerId = "default-invoker";
        let logs = [Log.constructFromObject({
            apiId,
            apiName,
            apiVersion,
            resourceName,
            protocol,
            operation,
            result
        })];
        let invocationLog = InvocationLog.constructFromObject({
            aefId,
            apiInvokerId,
            logs
        })
        my_default_api.apiInvocationLogsV1AefIdLogsPost(aefId, invocationLog, callback);
        next();
    }
}

module.exports = {
    capifAef
}