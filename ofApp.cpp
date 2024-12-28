#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(250, 3);
	this->base_mesh = ico_sphere.getMesh();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	this->draw_mesh.clear();

	if (ofGetFrameNum() % 50 < 20) {

		this->noise_step += ofMap(ofGetFrameNum() % 50, 0, 20, 0.25, 0);
	}

	vector<ofColor> color_list = { ofColor(38) };

	auto noise_seed = ofRandom(1000);
	for (int k = 0; k < color_list.size(); k++) {

		noise_seed += ofRandom(1000);
		for (auto v : this->base_mesh.getVertices()) {

			for (int i = 0; i < 1; i++) {

				auto radius = ofMap(ofNoise(glm::vec4(v.x * 0.0065, v.y * 0.0065, v.z * 0.0065, this->noise_step)), 0, 1, 150, 300);
				v = glm::normalize(v) * radius;
			}

			this->draw_mesh.addVertex(v);
			this->draw_mesh.addColor(color_list[k]);
		}

		for (int i = 0; i < this->base_mesh.getNumIndices(); i++) {

			this->draw_mesh.addIndex(this->base_mesh.getIndex(i));
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.72);

	this->draw_mesh.drawWireframe();

	ofFill();
	for (int i = 0; i < this->draw_mesh.getNumVertices(); i++) {

		ofDrawSphere(this->draw_mesh.getVertex(i), 2);
	}

	this->cam.end();

	/*
	int start = 50;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}