//
// Created by msegura on 13/06/19.
//

#include "KeyValue.h"

KeyValue::KeyValue() {}

KeyValue::KeyValue(string key, string value) {
    this->key=key;
    this->value=value;
}
KeyValue::KeyValue(string key, string operator_, string value) {
    this->key=key;
    this->value=value;
    this->operator_=operator_;
}

string KeyValue::getKey() {
    return this->key;
}

string KeyValue::getValue() {
    return this->value;
}

string KeyValue::getOperator() {
    return this->operator_;
}