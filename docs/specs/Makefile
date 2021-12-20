yamls := $(wildcard 29222-capif_stage3-h20/TS29222*.yaml)
specs := $(patsubst %.yaml, %.spec, $(yamls))
htmls := $(patsubst %.yaml, %.html, $(yamls))
output_dir=./build
doc_output_dir=./build/doc
generator=cpp-pistache-server

server-stub: $(specs)
docs: $(htmls)

publish-service: 29222-capif_stage3-h20/TS29222_CAPIF_Publish_Service_API.spec

discover-service: 29222-capif_stage3-h20/TS29222_CAPIF_Discover_Service_API.spec

%.spec: %.yaml
	openapi-generator-cli generate -o $(output_dir) -g $(generator) -i $^

%.html: %.yaml
	redoc-cli bundle -o $(doc_output_dir)/$@ $^

$(output_dir):
	mkdir $(output_dir)

$(doc_output_dir):
	mkdir $(doc_output_dir)

clean:
	rm -rf $(output_dir)
	rm -rf $(doc_output_dir)
