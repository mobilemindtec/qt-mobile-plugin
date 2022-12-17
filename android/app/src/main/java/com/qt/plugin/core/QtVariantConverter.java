package com.qt.plugin.core;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

public class QtVariantConverter {

    static public QtVariantMap fromMap(Map map){
        QtVariantMap result = new QtVariantMap();
        for(Object _key : map.keySet()){
            Object val  = map.get(_key);
            String key = _key.toString();
            if(val instanceof Map){
                result.put(key, fromMap((Map) val));
            }else if(val instanceof List){
                result.put(key, fromList((List) val));
            }else{
                result.putValue(key, QtVariant.from(val));
            }
        }
        return result;
    }

    static public QtVariantList fromList(List list){
        QtVariantList result = new QtVariantList();
        for(Object val : list){
            if(val instanceof Map){
                result.add(fromMap((Map) val));
            }else if(val instanceof List){
                result.add(fromList((List) val));
            }else{
                result.add(QtVariant.from(val));
            }
        }
        return result;
    }

    static public Map<String, Object> toMap(QtVariantMap map){
        Map<String, Object> result = new HashMap<>();
        for(String key : map.keySet()){
            IQtVariant variant = map.get(key);
            if(variant.isVariant()){
                result.put(key, ((QtVariant) variant).getValue());
            }else if(variant.isMap()){
                result.put(key, toMap((QtVariantMap) variant));
            }else if(variant.isList()){
                result.put(key, toList((QtVariantList) variant));
            }
        }
        return result;
    }

    static public List toList(QtVariantList list){
        List result = new LinkedList();
        for(IQtVariant variant : list){
            if(variant.isVariant()){
                result.add(((QtVariant) variant).getValue());
            }else if(variant.isMap()){
                result.add(toMap((QtVariantMap) variant));
            }else if(variant.isList()){
                result.add(toList((QtVariantList) variant));
            }
        }
        return result;
    }

}
