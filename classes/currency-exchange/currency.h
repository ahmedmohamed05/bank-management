#pragma once
#include "../../public/cstring.h"
#include <fstream>
#include <iostream>
#include <vector>

class Currency {
  std::string _country, _code, _currencyName;
  float _rate;

  enum status { valid, notValid };
  status _status = status::notValid;

  Currency(std::string country, std::string code, std::string currencyName,
           float rate) {
    _country = country;
    _code = code;
    _currencyName = currencyName;
    _rate = rate;
    _status = status::valid;
  }

  static Currency _convertLineToObject(std::string line) {
    std::vector<std::string> v = Mstring::split(line, " | ");
    return Currency(v.at(0), v.at(1), v.at(2), stof(v.at(3)));
  }

  static std::string _convertObjectToLine(Currency &c) {
    std::string line = c.getCountry() + " | ";
    line += c.getCode() + " | ";
    line += c.getCurrencyName() + " | ";
    line += std::to_string(c.getRate());
    return line;
  }

  static std::vector<Currency> _loadCurrencies() {
    std::fstream file("currencies.txt", std::ios::in);

    if (file.is_open()) {
      std::vector<Currency> currencies;
      std::string line;

      while (getline(file, line)) {
        Currency currency = _convertLineToObject(line);
        currencies.push_back(currency);
      }

      file.close();
      return currencies;
    } else {
      std::cout << "Error while loading currencies file\n";
      exit(EXIT_FAILURE);
    }
  }

  void _updateRate() {
    std::vector<Currency> currencies = _loadCurrencies();
    for (Currency &c : currencies) {
      if (this->_code == c.getCode()) {
        c = *this;
        break;
      }
    }
    std::fstream file("currencies.txt", std::ios::out);

    if (file.is_open()) {
      for (Currency &c : currencies) {
        file << _convertObjectToLine(c) << '\n';
      }

      file.close();
    } else {
      std::cout << "Error can't update file rates, File not opened\n";
      exit(EXIT_FAILURE);
    }
  }

public:
  Currency() { _status = status::notValid; }

  void setRate(float rate) {
    if (rate <= 0)
      return;
    _rate = rate;
    _updateRate();
  }
  float getRate() { return _rate; };

  std::string getCountry() { return _country; }
  std::string getCode() { return _code; }
  std::string getCurrencyName() { return _currencyName; }
  bool isValid() { return _status == status::valid; }
  status getStatus() { return _status; }

  // find currency using country name or code
  // you can check if the currency found by isValid method
  static Currency find(std::string str) {
    std::vector<Currency> currencies = _loadCurrencies();

    bool byCode = str.length() == 3;
    Mstring::toUpperCase(str);

    for (Currency &c : currencies) {
      // search using currency code
      if (byCode) {
        if (str == c.getCode()) {
          return c;
        }
      }

      // Search using country name
      else {
        // todo: Edit this shit
        Mstring s(c.getCountry());
        s.toUpperCase();
        if (str == s.getValue()) {
          return c;
        }
      }
    }

    return Currency();
  }

  static std::vector<Currency> getCurrencies() { return _loadCurrencies(); }
};