#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	for (int k = 0; k < 3; k++) {

		auto param = glm::vec3(15, 0, 0);
		auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
		auto start_index = this->face.getNumVertices();

		ofColor color;
		for (int i = 0; i < 150; i++) {

			int index = this->face.getNumVertices();

			auto location = glm::vec3(
				ofMap(ofNoise(noise_seed.x, (i + ofGetFrameNum()) * 0.01), 0, 1, -500, 500),
				ofMap(ofNoise(noise_seed.y, (i + ofGetFrameNum()) * 0.01), 0, 1, -500, 500),
				ofMap(ofNoise(noise_seed.z, (i + ofGetFrameNum()) * 0.01), 0, 1, -500, 500));

			this->face.addVertex(location + param);
			this->face.addVertex(location - param);

			auto alpha = 255;
			color.setHsb((ofGetFrameNum() + i + k * 85) % 255, 180, 255, alpha);

			this->face.addColor(color);
			this->face.addColor(color);

			this->frame.addVertex(location + param);
			this->frame.addVertex(location - param);

			this->frame.addColor(ofColor(39, alpha));
			this->frame.addColor(ofColor(39, alpha));

			if (i > 0) {

				this->face.addIndex(index + 0); this->face.addIndex(index - 1); this->face.addIndex(index - 2);
				this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index - 1);

				this->frame.addIndex(index + 0); this->frame.addIndex(index - 2);
				this->frame.addIndex(index + 1); this->frame.addIndex(index - 1);
			}
		}

		this->frame.addIndex(start_index + 0); this->frame.addIndex(start_index + 1);
		this->frame.addIndex(frame.getNumVertices() - 1); this->frame.addIndex(frame.getNumVertices() - 2);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	auto target = this->face.getVertex(this->face.getNumVertices() - 1);
	auto camera_location = this->face.getVertex(0) + glm::vec3(0, 0, 1200);

	this->cam.setPosition(camera_location);
	this->cam.setTarget(target);
	this->cam.lookAt(target);

	this->cam.begin();

	this->face.drawFaces();

	ofSetColor(239);
	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}