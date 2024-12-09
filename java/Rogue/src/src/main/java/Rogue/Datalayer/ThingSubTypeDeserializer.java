package Rogue.Datalayer;

import Rogue.Domain.Thing.ThingEnums.*;

import java.util.Arrays;

import com.google.gson.JsonDeserializationContext;
import com.google.gson.JsonDeserializer;
import com.google.gson.JsonElement;
import com.google.gson.JsonParseException;
import java.lang.reflect.Type;
import java.lang.reflect.Method;

public class ThingSubTypeDeserializer implements JsonDeserializer<ThingSubType> {

  @Override
  public ThingSubType deserialize(JsonElement json, Type typeOfT, JsonDeserializationContext context)
      throws JsonParseException {
    try {
      int value = json.getAsInt();
      return tryGetSubTypeByValue(value);
    } catch (NumberFormatException e) {
      String enumName = json.getAsString();
      ThingSubType result = tryGetSubTypeByName(enumName);
      if (result != null) {
        return result;
      }
    }
    throw new JsonParseException("Unknown ThingSubType value: " + json);
  }

  private ThingSubType tryGetSubTypeByValue(int value) {
    for (Class<? extends ThingSubType> clazz : Arrays.asList(WeaponSubType.class, ScrollSubType.class,
        OtherSubType.class, ElixirSubType.class)) {
      try {
        Method method = clazz.getMethod("getByValue", int.class);
        Object obj = method.invoke(null, value);
        if (obj instanceof ThingSubType) {
          return (ThingSubType) obj;
        }
      } catch (Exception e) {
        //
      }
    }
    return null;
  }

  private ThingSubType tryGetSubTypeByName(String enumName) {
    for (Class<? extends ThingSubType> clazz : Arrays.asList(WeaponSubType.class, ScrollSubType.class,
        OtherSubType.class, ElixirSubType.class)) {
      try {
        Method valueOf = clazz.getMethod("valueOf", String.class);
        Object obj = valueOf.invoke(null, enumName);
        if (obj instanceof ThingSubType) {
          return (ThingSubType) obj;
        }
      } catch (Exception ex) {
        //
      }
    }
    return null;
  }
}