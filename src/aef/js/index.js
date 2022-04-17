const capifApfClient = require('capif-aef-client');
const { ccfUrl } = require('./config');
const { ApiClient, DefaultApi, InvocationLog, Log } = capifApfClient;

const myApiClient = new ApiClient(ccfUrl);
const myDefaultApi = new DefaultApi(myApiClient);

/**
 * Express middleware of CAPIF AEF
 * @param {String} aefId The identity of this API exposing function
 * @param {String} apiId The registed identity of this API assigned by CCF
 * @param {String} protocol The protocol of this AEF. Possible value are "HTTP_1_1" or "HTTP_2"
 */
function capifAef(aefId, apiId = "0000", protocol = "HTTP_1_1") {
    return (req, res, next) => {
        let capifLogCallback = (error, data, response) => {
            if (error) {
                console.error("[CAPIF][AEF] Error occurs while logging")
                console.error(error);
            }
        };

        // Prepare argument of logging
        let url = req.originalUrl.split('/');
        let apiName = url[0];
        let apiVersion = url[1];
        let resourceName = url.slice(2).join('/');
        let operation = req.method;
        let invocationTime = new Date().toISOString();

        // [TODO] Get invoker ID by authentication
        let apiInvokerId = "default-invoker";

        // Setup hook to get status code of response
        let origEnd = res.end;
        res.end = function (chunk, encoding) {
            let result = res.statusCode;

            // Prepare the structure for calling
            let logs = [Log.constructFromObject({
                apiId,
                apiName,
                apiVersion,
                resourceName,
                protocol,
                operation,
                result,
                invocationTime
            })];
            let invocationLog = InvocationLog.constructFromObject({
                aefId,
                apiInvokerId,
                logs
            })
            myDefaultApi.apiInvocationLogsV1AefIdLogsPost(aefId, invocationLog, capifLogCallback);

            // Restore the origin end hook
            res.end = origEnd;
            res.end(chunk, encoding);
        };
        next();
    }
}

module.exports = {
    capifAef
}