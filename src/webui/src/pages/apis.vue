<template>
    <div>
        <div class="input-group mb-3">
            <span class="input-group-text">APF ID</span>
            <input type="text" class="form-control" v-model="apf_id" />
            <button class="btn btn-primary" type="button" @click="queryApf">Query</button>
        </div>
        <table class="table table-striped">
            <thead>
                <tr>
                    <th scope="col">#</th>
                    <th scope="col">API Name</th>
                    <th scope="col">AEF ID</th>
                    <th scope="col">Versions</th>
                    <th scope="col">Domain Name</th>
                </tr>
            </thead>
            <tbody>
                <tr v-for="(api, index) in apis">
                    <th scope="row">{{ index }}</th>
                    <td>{{ api.name }}</td>
                    <td>{{ api.aef_id }}</td>
                    <td>{{ api.versions.join(', ') }}</td>
                    <td>{{ api.domain }}</td>
                </tr>
            </tbody>
        </table>
        <router-link
            to="/new"
            class="btn btn-outline-secondary mx-auto d-block"
            style="width: 13rem;"
        >Publish New API</router-link>
    </div>
</template>

<script>
const { ccfUrl } = require('../../config/ccf.js');
const capifWebUiClient = require('capif-webui-client');
const { ApiClient, DefaultApi, ServiceAPIDescription } = capifWebUiClient;
export default {
    name: "apis",
    data() {
        return {
            apis: [],
            apf_id: ""
        };
    },
    methods: {
        queryApf: function () {
            const my_api_client = new ApiClient(ccfUrl);
            const my_default_api = new DefaultApi(my_api_client);
            var callback = (error, data) => {
                if (error) {
                    console.error(error);
                } else {
                    console.log('API called successfully. Returned data: ');
                    console.log(JSON.stringify(data, null, 2));
                    this.apis = data.map(api => {
                        let aefProfiles = api['aefProfiles'];
                        if (aefProfiles === undefined) {
                            return {
                                name: api['apiName'],
                                aef_id: "",
                                versions: [],
                                domain: ""
                            }
                        } else {
                            let aefProfile = api['aefProfiles'][0];
                            let versions = aefProfile["versions"].map(v => v["apiVersion"]);
                            return {
                                name: api['apiName'],
                                aef_id: aefProfile["aefId"],
                                versions,
                                domain: aefProfile["domainName"]
                            }
                        }
                    })
                }
            };
            my_default_api.publishedApisV1ApfIdServiceApisGet(this.apf_id, callback);
        }
    },
};
</script>

<style scoped>
</style>