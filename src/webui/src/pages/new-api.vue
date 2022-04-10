<template>
  <div>
    <form @submit="publishApi">
      <div class="mb-3">
        <label for="apiName" class="form-label">API Name</label>
        <input
          type="text"
          class="form-control"
          id="apiName"
          placeholder="example-api"
          v-model="api_name"
          required
        />
      </div>
      <div class="mb-3">
        <label for="apfId" class="form-label">APF ID</label>
        <input
          type="text"
          class="form-control"
          id="apfId"
          placeholder="Identity for API Publishing Function"
          v-model="apf_id"
          required
        />
      </div>
      <div class="mb-3">
        <label for="aefId" class="form-label">AEF ID</label>
        <input
          type="text"
          class="form-control"
          id="aefId"
          placeholder="Identity for API Exposing Function"
          v-model="aef_id"
          required
        />
      </div>
      <div class="mb-3">
        <label for="versions" class="form-label">Versions</label>
        <input
          type="text"
          class="form-control"
          id="versions"
          placeholder="v1 or v1,v2 ..."
          v-model="versions"
          required
        />
      </div>
      <div class="mb-3">
        <label for="domainName" class="form-label">Domain Name</label>
        <input
          type="text"
          class="form-control"
          id="domainName"
          placeholder="The FQDN for API Exposing Function"
          v-model="domain"
          required
        />
      </div>
      <button
        type="submit"
        class="btn btn-outline-secondary mx-auto d-block"
        style="width: 13rem;"
      >Publish New API</button>
    </form>
    <transition>
      <div class="alert alert-success mt-3" style role="alert" v-if="show">
        <p class="mb-0">
          <strong>🎉 New API has successfully published</strong>
        </p>
      </div>
    </transition>
  </div>
</template>

<script>
const { ccfUrl } = require('../../config/ccf.js');
const capifWebUiClient = require('capif-webui-client');
const { ApiClient, DefaultApi, ServiceAPIDescription } = capifWebUiClient;
export default {
  name: "new-api",
  data() {
    return {
      api_name: "",
      apf_id: "",
      aef_id: "",
      versions: "",
      domain: "",
      show: false
    };
  },
  methods: {
    publishApi: function (e) {
      e.preventDefault();

      const my_api_client = new ApiClient(ccfUrl);
      const my_default_api = new DefaultApi(my_api_client);

      let newServiceAPIDescription = {
        apiName: this.api_name,
        aefProfiles: [
          {
            aefId: this.aef_id,
            versions: this.versions.split(',').map(v => { return { apiVersion: v.trim() } }),
            domainName: this.domain
          }
        ]
      };

      var callback = (error, data, response) => {
        if (error) {
          console.error(error);
        } else {
          console.log('API called successfully. Returned data: ');
          console.log(JSON.stringify(data, null, 2));
          this.successPublish();
        }
      };

      my_default_api.publishedApisV1ApfIdServiceApisPost(
        this.apf_id,
        newServiceAPIDescription,
        callback
      );
    },
    successPublish: function () {
      this.api_name = "";
      this.apf_id = "";
      this.aef_id = "";
      this.versions = "";
      this.domain = "";
      this.show = true;
      window.setTimeout(() => {
        this.show = false;
      }, 2000);
    }
  },
};
</script>

<style scoped>
.v-leave {
  opacity: 1;
}
.v-leave-active {
  transition: opacity 0.2s;
}
.v-leave-to {
  opacity: 0;
}
</style>
