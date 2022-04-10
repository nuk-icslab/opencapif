const capifInvkrClient = require('capif-invkr-client');
const { ccfUrl } = require('./config');
const { ApiClient, DefaultApi, ServiceAPIDescription, APIInvokerEnrolmentDetails } = capifInvkrClient;

const my_api_client = new ApiClient(ccfUrl);
const my_default_api = new DefaultApi(my_api_client);

var invkr_id = undefined;

function onboardInvoker(public_key, notif_dest) {
    return new Promise((resolve, reject) => {
        if (invkr_id != undefined) {
            resolve(invkr_id);
            return;
        }
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
                invkr_id = data['apiInvokerId'];
                console.log(`[CAPIF][API Invoker] Onboarded; My Invoker ID is: ${invkr_id}`);
                resolve(invkr_id);
            }
        };
        my_default_api.apiInvokerManagementV1OnboardedInvokersPost(newApiInvokerEnrolmentDetils, callback);
    });
}

async function discoverApi(api_name) {
    if (invkr_id === undefined) {
        invkr_id = await onboardInvoker();
    }
    return new Promise((resolve, reject) => {
        if (api_name === undefined || api_name === null) {
            reject({ msg: "API name is mandatory" });
            return;
        }
        let opt = {
            apiName: api_name
        }

        let callback = (error, data, response) => {
            if (error) {
                console.error("[CAPIF][API Invoker] Error occurs while discovering")
                console.error(error);
                reject(error);
            } else {
                for (service_api_description of data['serviceAPIDescriptions']) {
                    if (service_api_description['aefProfiles'] !== undefined) {
                        for (aef_profile of service_api_description['aefProfiles']) {
                            let version = aef_profile['versions'][0]['apiVersion'];
                            let url = `https://${aef_profile['domainName']}/${api_name}/${version}`;
                            console.log(`[CAPIF][API Invoker] Found AEF: ${url}`);
                            resolve(url);
                            return;
                        }
                    }
                }
                reject({ msg: "AEF not found" });
            }
        };
        my_default_api.serviceApisV1AllServiceAPIsGet(invkr_id, opt, callback);
    });
}


module.exports = {
    onboardInvoker,
    discoverApi
}