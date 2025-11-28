// Google Docs Low Level Design (LLD) Example
#include <iostream>
#include <string>
#include <vector>

class Document {
	std::string title;
	std::string content;
public:
	Document(const std::string& t) : title(t) {}
	void addContent(const std::string& text) {
		content += text;
	}
	void show() const {
		std::cout << "Title: " << title << "\nContent: " << content << std::endl;
	}
};

int main() {
	Document doc("My Google Doc");
	doc.addContent("Hello, this is a collaborative document. ");
	doc.addContent("Multiple users can edit in real-time.");
	doc.show();
	return 0;
}