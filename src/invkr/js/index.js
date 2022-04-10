const capifInvkrClient = require('capif-invkr-client');
const { ccfUrl } = require('./config');
const { ApiClient, DefaultApi, ServiceAPIDescription, APIInvokerEnrolmentDetails } = capifInvkrClient;

const my_api_client = new ApiClient(ccfUrl);
const my_default_api = new DefaultApi(my_api_client);

function onboardInvoker(public_key, notif_dest) {
    return new Promise((resolve, reject) => {
        public_key = public_key || "noPublicKey";
        notif_dest = notif_dest || "noNotifDest";
        let newApiInvokerEnrolmentDetils = APIInvokerEnrolmentDetails.constructFromObject({
            onboardingInformation: {
                apiInvokerPublicKey: public_key
            },
            notificationDestination: notif_dest
        })

        let callback = (error, data, response) => {
            if (error) {
                console.error("[CAPIF][API Invoker] Error occurs while onboarding")
                console.error(error);
                reject(error);
            } else {
                console.log('API called successfully. Returned data: ');
                console.log(JSON.stringify(data, null, 2));
                resolve(data);
            }
        };
        my_default_api.apiInvokerManagementV1OnboardedInvokersPost(newApiInvokerEnrolmentDetils, callback);
    });
}

function discoverApi() {

}


module.exports = {
    onboardInvoker,
    discoverApi
}