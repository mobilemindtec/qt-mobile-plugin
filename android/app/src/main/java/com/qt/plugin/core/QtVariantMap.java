package com.qt.plugin.core;

import java.util.HashMap;
import java.util.Map;

public class QtVariantMap extends HashMap<String, IQtVariant> implements  IQtVariant {

    public static QtVariantMap from(Map map){
        QtVariantMap result = new QtVariantMap();
        for(Object key : map.keySet()){
            result.putValue(key.toString(), QtVariant.from(map.get(key)));
        }
        return result;
    }

    public void putValue(String key, Object value){
        super.put(key, QtVariant.from(value));
    }

    @Override
    public IQtVariant toVariant() {
        return this;
    }

    @Override
    public boolean isList() {
        return false;
    }

    @Override
    public boolean isVariant() {
        return false;
    }

    @Override
    public boolean isMap() {
        return true;
    }

    public Map<String, Object> toMap(){
        return  QtVariantConverter.toMap(this);
    }
}
