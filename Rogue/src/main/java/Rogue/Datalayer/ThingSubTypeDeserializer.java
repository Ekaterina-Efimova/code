package Rogue.Datalayer;

import java.util.Arrays;
import java.util.logging.Level;
import java.util.logging.Logger;

import com.google.gson.JsonDeserializationContext;
import com.google.gson.JsonDeserializer;
import com.google.gson.JsonElement;
import com.google.gson.JsonParseException;

import Rogue.Domain.Game.Objects.Thing.ThingEnums.*;

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
        if (obj instanceof ThingSubType thing) {
          return thing;
        }
      } catch (Exception e) {
        Logger.getLogger(ThingSubTypeDeserializer.class.getName()).log(Level.SEVERE, "An error occurred", e);
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
        if (obj instanceof ThingSubType thing) {
          return thing;
        }
      } catch (Exception e) {
        Logger.getLogger(ThingSubTypeDeserializer.class.getName()).log(Level.SEVERE, "An error occurred", e);
      }
    }
    return null;
  }
}