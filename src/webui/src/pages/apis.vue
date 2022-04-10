<template>
    <div>
        <div class="input-group mb-3">
            <span class="input-group-text">APF ID</span>
            <input type="text" class="form-control" v-model="apf_id" />
            <button class="btn btn-outline-secondary" type="button" @click="queryApf">Query</button>
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
            class="btn btn-success mx-auto d-block"
            style="width: 13rem;"
        >Publish New API</router-link>
    </div>
</template>

<script>
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
            const capifWebUiClient = require('capif-webui-client');
            const { ApiClient, DefaultApi, ServiceAPIDescription } = capifWebUiClient;
            const my_api_client = new ApiClient("http://127.0.0.1:8080");
            const my_default_api = new DefaultApi(my_api_client);
            let apf_id = this.apf_id;
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
                            let versions = aefProfile["versions"].map(ver => {
                                ver["apiVersion"]
                            })
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
            my_default_api.publishedApisV1ApfIdServiceApisGet(apf_id, callback);
        }
    },
};
</script>

<style scoped>
</style>