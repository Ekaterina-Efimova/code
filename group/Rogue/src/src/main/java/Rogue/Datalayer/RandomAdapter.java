package Rogue.Datalayer;

import com.google.gson.JsonDeserializationContext;
import com.google.gson.JsonDeserializer;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParseException;
import com.google.gson.JsonSerializationContext;
import com.google.gson.JsonSerializer;
import java.lang.reflect.Type;
import java.util.Random;

public class RandomAdapter implements JsonSerializer<Random>, JsonDeserializer<Random> {
  @Override
  public JsonElement serialize(Random src, Type typeOfSrc, JsonSerializationContext context) {
    JsonObject jsonObject = new JsonObject();
    jsonObject.addProperty("seed", src.nextLong());
    return jsonObject;
  }

  @Override
  public Random deserialize(JsonElement json, Type typeOfT, JsonDeserializationContext context)
      throws JsonParseException {
    JsonObject jsonObject = json.getAsJsonObject();
    long seed = jsonObject.get("seed").getAsLong();
    return new Random(seed);
  }
}