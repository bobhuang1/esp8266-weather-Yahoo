#include <ESPWiFi.h>
#include <WiFiClientSecure.h>
#include "YahooWeather.h"

YahooWeather::YahooWeather() {

}

uint8_t YahooWeather::updateWeather(YahooWeatherCurrentData *data, YahooWeatherForecastData *data1, String location) {
	return doUpdate(data, data1, "/v1/public/yql?q=select%20*%20from%20weather.forecast%20where%20woeid%20in%20(" + location + ")%20and%20u%3D'" + "c" + "'&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys");
	// http://query.yahooapis.com/v1/public/yql?q=select%20*%20from%20weather.forecast%20where%20woeid%20in%20(2132619)%20and%20u%3D'c'&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys
}

uint8_t YahooWeather::doUpdate(YahooWeatherCurrentData *data, YahooWeatherForecastData *data1, String url) {
	unsigned long lostTest = 60000UL;
	unsigned long lost_do = millis();
	this->weatherItemCounter = 0;
	this->currentForecast = 0;
	this->data = data;
	this->data1 = data1;
	JsonStreamingParser parser;
	parser.setListener(this);

	Serial.printf("Getting url: %s\n", url.c_str());

	WiFiClientSecure client;

	Serial.println("query.yahooapis.com");
	if (!client.connect("query.yahooapis.com", 443)) {
		Serial.println("connection failed");
		return 0;
	}

	client.print(String("GET ") + url + " HTTP/1.1\r\n" +
		"Host: " + "query.yahooapis.com" + "\r\n" +
		"User-Agent: INTERNET EXPLORER\r\n" +
		"Connection: close\r\n\r\n");

	Serial.println("request sent");

	int retryCounter = 0;
	while (!client.available()) {
		Serial.println(".");
		delay(1000);
		retryCounter++;
		if (retryCounter > 10) {
			return 0;
		}
	}

	int pos = 0;
	boolean isBody = false;
	char c;

	int size = 0;
	client.setNoDelay(false);
	while (client.connected()) {
		while ((size = client.available()) > 0) {
/*			if ((millis() - lost_do) > lostTest) {
				Serial.println("lost in client with a timeout");
				client.stop();
				ESP.restart();
			}
*/
			c = client.read();
			if (c == '{' || c == '[') {
				isBody = true;
			}
			if (isBody) {
				parser.parse(c);
//				Serial.print(c);
			}
		}
	}
	this->data = nullptr;
	this->data1 = nullptr;
	return currentForecast;
}

void YahooWeather::whitespace(char c) {
	Serial.println("whitespace");
}

void YahooWeather::startDocument() {
	Serial.println("start document");
}

void YahooWeather::key(String key) {
	currentKey = String(key);
	Serial.println("Key: " + currentKey);
}

void YahooWeather::value(String value) {
	Serial.println("value: " + value);
		Serial.println("Value "+ value + " currentParent is: " + currentParent + " and currentKey is " + currentKey);

		if (currentParent == "wind") {
		if (currentKey == "direction") {
			this->data->direction = value.toInt();
			Serial.println("wind: " + value);
		}
		if (currentKey == "speed") {
			this->data->speed = value.toFloat();
		}
	}

	if (currentParent == "atmosphere") {
		if (currentKey == "humidity") {
			this->data->humidity = value.toInt();
		}
		if (currentKey == "pressure") {
			this->data->pressure = value.toFloat();
		}
	}

	if (currentParent == "condition") {
		if (currentKey == "code") {
			this->data->code = value;
			this->data->iconMeteoCon = getMeteoconIcon(value);
		}
		if (currentKey == "temp") {
			this->data->temp = value.toInt();
		}
		if (currentKey == "text") {
			this->data->text = value;
		}
	}

	if (currentParent == "forecast") {
		if (currentKey == "date") {
			data1[currentForecast].date = value;
			Serial.println(value);
		}
		if (currentKey == "code") {
			data1[currentForecast].code = value;
			data1[currentForecast].iconMeteoCon = getMeteoconIcon(value);
		}
		if (currentKey == "day") {
			data1[currentForecast].day = value;
		}
		if (currentKey == "high") {
			data1[currentForecast].high = value.toInt();
		}
		if (currentKey == "low") {
			data1[currentForecast].low = value.toInt();
		}
		if (currentKey == "text") {
			data1[currentForecast].text = value;
			currentForecast++;
		}
	}
}

void YahooWeather::endArray() {
	Serial.println("endArray");
}


void YahooWeather::startObject() {
	currentParent = currentKey;
	Serial.println("startObject " + currentKey);

}

void YahooWeather::endObject() {
	if (currentParent == "forecast") {
		weatherItemCounter++;
	}
	currentParent = "";
	Serial.println("endObject " + currentKey);
}

void YahooWeather::endDocument() {
	Serial.println("endDocument");

}

void YahooWeather::startArray() {
	Serial.println("startArray");

}


String YahooWeather::getMeteoconIcon(String code) {
	if (code == "0") {
		return "";
	}
	if (code == "1") {
		return "";
	}
	if (code == "2") {
		return "";
	}
	if (code == "3") {
		return "";
	}
	if (code == "4") {
		return "";
	}
	if (code == "5") {
		return "";
	}
	if (code == "6") {
		return "";
	}
	if (code == "7") {
		return "";
	}
	if (code == "8") {
		return "";
	}
	if (code == "9") {
		return "";
	}
	if (code == "10") {
		return "";
	}
	if (code == "11") {
		return "";
	}
	if (code == "12") {
		return "";
	}
	if (code == "13") {
		return "";
	}
	if (code == "14") {
		return "";
	}
	if (code == "15") {
		return "";
	}
	if (code == "16") {
		return "";
	}
	if (code == "17") {
		return "";
	}
	if (code == "18") {
		return "";
	}
	if (code == "19") {
		return "";
	}
	if (code == "20") {
		return "";
	}
	if (code == "21") {
		return "";
	}
	if (code == "22") {
		return "";
	}
	if (code == "23") {
		return "";
	}
	if (code == "24") {
		return "";
	}
	if (code == "25") {
		return "";
	}
	if (code == "26") {
		return "";
	}
	if (code == "27") {
		return "";
	}
	if (code == "28") {
		return "";
	}
	if (code == "29") {
		return "";
	}
	if (code == "30") {
		return "";
	}
	if (code == "31") {
		return "";
	}
	if (code == "32") {
		return "";
	}
	if (code == "33") {
		return "";
	}
	if (code == "34") {
		return "";
	}
	if (code == "35") {
		return "";
	}
	if (code == "36") {
		return "";
	}
	if (code == "37") {
		return "";
	}
	if (code == "38") {
		return "";
	}
	if (code == "39") {
		return "";
	}
	if (code == "40") {
		return "";
	}
	if (code == "41") {
		return "";
	}
	if (code == "42") {
		return "";
	}
	if (code == "43") {
		return "";
	}
	if (code == "44") {
		return "";
	}
	if (code == "45") {
		return "";
	}
	if (code == "46") {
		return "";
	}
	if (code == "47") {
		return "";
	}

	// Nothing matched: N/A
	return ")";
}
