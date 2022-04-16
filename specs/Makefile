spec_src_dir := $(abspath 29222-capif_stage3-h40)
output_dir := $(abspath ../lib/openapi)
spec_output_dir := $(abspath ./build/compiled_spec)
doc_output_dir := $(abspath ./build/docs)
tmp_dir := /tmp/capif

yamls := $(wildcard $(spec_src_dir)/TS*.yaml)
capif_yamls := $(wildcard $(spec_src_dir)/TS29222_CAPIF*.yaml)
capif_htmls := $(patsubst $(spec_src_dir)/%.yaml, $(doc_output_dir)/%.html, $(capif_yamls))

merged_api_version := 17.4.0

generator_flag := --skip-validate-spec

.PHONY: all, docs, clean

.PHONY: ccf-pistache, ccf-restbed, ccf-qhttpengine

.POHNY: aef-restsdk, aef-js, invkr-js, webui-js, clean

all: ccf-pistache aef-js invkr-js webui-js

docs: $(capif_htmls)

ccf-pistache: $(spec_output_dir)/ccf.yaml
	mkdir -p $(output_dir)/$@
	openapi-generator-cli generate -o $(output_dir)/$@ \
	  -g cpp-pistache-server $(generator_flag) \
	  -i $^

ccf-restbed: $(spec_output_dir)/ccf.yaml
	mkdir -p $(output_dir)/$@
	openapi-generator-cli generate -o $(output_dir)/$@ \
	  -g cpp-restbed-server $(generator_flag) \
	  -i $^

ccf-qhttpengine: $(spec_output_dir)/ccf.yaml
	mkdir -p $(output_dir)/$@
	openapi-generator-cli generate -o $(output_dir)/$@ \
	  -g cpp-qt-qhttpengine-server $(generator_flag) \
	  -i $^

aef-restsdk: $(spec_output_dir)/aef.yaml
	mkdir -p $(output_dir)/$@
	openapi-generator-cli generate -o $(output_dir)/$@ \
	  -g cpp-restsdk $(generator_flag) \
	  -i $^

aef-js: $(spec_output_dir)/aef.yaml
	mkdir -p $(output_dir)/$@
	openapi-generator-cli generate -o $(output_dir)/$@ \
	  -g javascript $(generator_flag) \
	  --additional-properties=projectName=capif-aef-client \
	  -i $^
	cd $(output_dir)/$@ && npm install && npm run build

invkr-js: $(spec_output_dir)/invkr.yaml
	mkdir -p $(output_dir)/$@
	openapi-generator-cli generate -o $(output_dir)/$@ \
	  -g javascript $(generator_flag) \
	  --additional-properties=projectName=capif-invkr-client \
	  -i $^
	cd $(output_dir)/$@ && npm install && npm run build

webui-js: $(spec_output_dir)/webui.yaml
	mkdir -p $(output_dir)/$@
	openapi-generator-cli generate -o $(output_dir)/$@ \
	  -g javascript $(generator_flag) \
	  --additional-properties=projectName=capif-webui-client \
	  -i $^
	cd $(output_dir)/$@ && npm install && npm run build

$(spec_output_dir)/%.yaml: openapi-merge-%.json $(yamls)
	mkdir -p $(@D)
	mkdir -p $(tmp_dir)

	@echo Merging used APIs\' specifications
	cp $^ $(tmp_dir)
	cd $(tmp_dir) && openapi-merge-cli -c $<

	# cp $(tmp_dir)/output.yaml $@
	# cp $(yamls) $(@D)

	@echo Compiling specifications to get rid off $$ref
	openapi-generator-cli generate -o $(tmp_dir) -g openapi-yaml -i $(tmp_dir)/output.yaml
	mv $(tmp_dir)/openapi/openapi.yaml $@

	# @echo Removing optional operationId to prevent duplication
	# yq -i 'del(.. | select(has("operationId")).operationId)' $@

	@echo Removing useless field
	yq -i 'del(.servers)' $@
	yq -i 'del(.externalDocs)' $@
	yq -i 'del(.info.description)' $@

	@echo Updating description
	yq -i '.info.title="Merged 3GPP CAPIF API. Based on $<"' $@
	yq -i '.info.version="$(merged_api_version)"' $@

	# @echo Validating the generated specification
	# openapi-generator-cli validate -i $@

	rm -rf $(tmp_dir)

$(doc_output_dir)/%.html: $(spec_src_dir)/%.yaml
	mkdir -p $(@D)
	redoc-cli build -o $@ $^

clean:
	rm -rf $(spec_output_dir)
	rm -rf $(doc_output_dir)
	rm -rf $(output_dir)
