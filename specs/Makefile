specs := $(patsubst %.yaml, %.spec, $(wildcard 29222-capif_stage3-h20/TS29222*.yaml))
output_dir=./build
generator=cpp-pistache-server

server-stub: $(specs)

publish-service: 29222-capif_stage3-h20/TS29222_CAPIF_Publish_Service_API.spec

%.spec: %.yaml
	openapi-generator-cli generate -o $(output_dir) -g $(generator) -i $^

$output_dir:
	mkdir $output_dir