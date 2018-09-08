#pragma once
#include <JsonListener.h>
#include <JsonStreamingParser.h>
#include <time.h>

typedef struct YahooWeatherCurrentData {
	// The following are under wind branch
	// 270, wind direction
	uint16_t direction;
	// 6.44, wind speed
	float speed;

	// The following are under atmosphere branch
	// 78, humidity
	uint8_t humidity;
	// 33931.63, pressure
	float pressure;

	// The following are under item/condition branch
	// 4
	String code;
	// 28, current temperature
	uint8_t temp;
	// Thunderstorms
	String text;
	// We will get MeteoCon from code
	String iconMeteoCon;
} YahooWeatherCurrentData;

typedef struct YahooWeatherForecastData {
	// All under forecast branch
	// 26 Jul 2018
	String date;
	// 4
	String code;
	// Thu
	String day;
	// 36
	uint8_t high;
	// 27
	uint8_t low;
	// Thunderstorms
	String text;
	// We will get MeteoCon from code
	String iconMeteoCon;
} YahooWeatherForecastData;


class YahooWeather : public JsonListener {
private:
	String currentKey;
	String currentParent;
	YahooWeatherCurrentData *data;
	YahooWeatherForecastData *data1;
	uint8_t weatherItemCounter = 0;
	uint8_t currentForecast;

	uint8_t doUpdate(YahooWeatherCurrentData *data, YahooWeatherForecastData *data1, String url);

public:
	YahooWeather();
	uint8_t updateWeather(YahooWeatherCurrentData *data, YahooWeatherForecastData *data1, String location);

	String getMeteoconIcon(String icon);
	virtual void whitespace(char c);

	virtual void startDocument();

	virtual void key(String key);

	virtual void value(String value);

	virtual void endArray();

	virtual void endObject();

	virtual void endDocument();

	virtual void startArray();

	virtual void startObject();
};
