package com.qt.plugin.core;

import java.util.List;
import java.util.Map;
import java.util.Objects;

public class QtVariant implements IQtVariant{

    private Object value;

    public QtVariant(){}

    public QtVariant(Object value){
        setValue(value);
    }

    public QtVariant(IQtVariant value){
        if(value.isList() || value.isMap()){
            setValue(value);
        }else{
            setValue(((QtVariant)value).getValue());
        }
    }

    public static QtVariant from(Object value){
        return new QtVariant(value);
    }

    public <T> T getValue() {
        return value != null ? (T) value : null;
    }

    public void setValue(Object value) {

        if(value instanceof Map){
            if(!(value instanceof QtVariantMap)){
                throw new QtMobilePluginChannelException("use QVariantMap to Map values");
            }
        }

        if(value instanceof List){
            if(!(value instanceof QtVariantList)){
                throw new QtMobilePluginChannelException("use QVariantList to List values");
            }
        }

        this.value = value;
    }

    public boolean isValueInt(){
        return value instanceof Integer;
    }

    public boolean isValueLong(){
        return value instanceof Long;
    }

    public boolean isValueDouble(){
        return value instanceof Double;
    }

    public boolean isValueFloat(){
        return value instanceof Float;
    }

    public boolean isValueBool(){
        return value instanceof Boolean;
    }

    public  boolean isValueVariant(){
        return value instanceof QtVariant;
    }

    public boolean isValueList(){
        return value instanceof List;
    }

    public boolean isValueMap(){
        return value instanceof Map;
    }

    public  boolean isValueNull(){
        return value == null;
    }

    @Override
    public boolean isVariant() {
        return true;
    }

    @Override
    public boolean isMap() {
        return false;
    }

    @Override
    public boolean isList() {
        return false;
    }

    @Override
    public IQtVariant toVariant() {
        return this;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        QtVariant qtVariant = (QtVariant) o;
        return Objects.equals(value, qtVariant.value);
    }

    @Override
    public int hashCode() {
        return Objects.hash(value);
    }
}
