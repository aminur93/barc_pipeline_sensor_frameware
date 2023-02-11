#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Hello world!\n");
    return 0;
}

char jsonOutput[128];

void loop(){

    if(WiFi.status() == WL_CONNECTED)
    {
        HTTPClient client;

        client.begin("https://test.nodesdigitalbd.com/api/sensor/store");
        client.addHeader("Content-Type", "application/json");

        const size_t CAPACITY = jSON_OBJECT_SIZE(4);
        StaticJsonObject<CAPACITY> doc;

        JsonObject object = doc.to<JsonObject>();

        object['mac_address'] = "";
        object['soil_mosture'] = "";
        object['soil_temperature'] = "";
        object['ec'] = "";

        serializeJson(doc, jsonOutput);

        int httpCode = client.POST(String(jsonOutput));

        if(httpCode > 0)
        {
            String.payload = client.getString();
            Serial.println("\nStatuscode" + String(httpCode));
            Serial.println(payload);

            client.end();
        }else{
            Serial.println("Error on http request")
        }
    }else{

        Serial.println("COnnection lost")
    }
}
