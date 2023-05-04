#include <iostream>
#include <map>
#include <list>
#include <algorithm>
#include <cmath>
using namespace std;

struct node{
    // list of example
    list<map<string, string>> instances;
    string target_value;
    string test_attribute;
    map<string, struct node> branch;
};

bool checkAllSame(list<map<string, string>> examples, const string& target_attribute){
    string value = examples.front()[target_attribute];
    for(map<string, string> item : examples){
        if(item[target_attribute] != value){
            return false;
        }
    }
    return true;
}

string findMostCommon(const list<map<string, string>>& examples, const string& target_attribute){
    map<string, int> counts;
    string mostCommon;
    int max = 0;
    for(map<string, string> example : examples){
        string value = example[target_attribute];
        if(counts.find(value) == counts.end()){
            counts.insert({value, 1});
        }
        else{
            counts[value]++;
        }
        if(counts[value] > max){
            max = counts[value];
            mostCommon = value;
        }
    }
    return mostCommon;
}

list<map<string, string>> filterExamples(const list<map<string, string>>& examples, const string& attribute, const string& attribute_value){
    list<map<string, string>> filteredExamples;
    for(auto example : examples){
        if(example[attribute] == attribute_value){
            filteredExamples.push_back(example);
        }
    }
    return filteredExamples;
}

double calcEntropy(const list<map<string, string>>& examples, const string& target_attribute){
    map<string, int> counts;
    list<string> values;
    for(map<string, string> example : examples){
        string value = example[target_attribute];
        if(counts.find(value) == counts.end()){
            counts.insert({value, 1});
            values.push_back(value);
        }
        else{
            counts[value]++;
        }
    }
    double entropy = 0;
    for(string v : values){
        double p = counts[v] / (double)examples.size();
        entropy -= p * log(p);
    }
    return entropy;
}

double calcInfoGain(const list<map<string, string>>& examples, const string& test_attribute, const string& target_attribute){
    map<string, list<map<string, string>>> groups;
    list<string> values;
    for(auto example : examples){
        string value = example[test_attribute];
        if(groups.find(value) == groups.end()){
            list<map<string, string>> one;
            one.push_back(example);
            groups.insert({value, one});
            values.push_back(value);
        }
        else{
            groups[value].push_back(example);
        }
    }
    double gain = calcEntropy(examples, target_attribute);
    for(const string& value : values){
        list<map<string, string>> group = groups[value];
        double p = (double)group.size() / (double)examples.size();
        double h = calcEntropy(group, target_attribute);
        gain -= p * h;
    }
    return gain;
}

string bestClassifier(const list<map<string, string>>& examples, const list<string>& attributes, const string& target_attribute){
    double max = 0;
    string bestClassifier;
    for(const string& attribute : attributes){
        double gain = calcInfoGain(examples, attribute, target_attribute);
        if(gain >= max){
            max = gain;
            bestClassifier = attribute;
        }
    }
    return bestClassifier;
}

struct node ID3(list<map<string, string>> examples, const string& target_attribute, const list<string>& attributes, map<string, list<string>> attribute_values){
    struct node decision;
    decision.instances = examples;
    if(checkAllSame(examples, target_attribute)){
        map<string, string> one = examples.front();
        decision.target_value = one[target_attribute];
        return decision;
    }
    if(attributes.empty()){
        string mostCommon = findMostCommon(examples, target_attribute);
        decision.target_value = mostCommon;
        return decision;
    }
    decision.test_attribute = bestClassifier(examples, attributes, target_attribute);
    for(const string& possible_value : attribute_values[decision.test_attribute]){
        list<map<string, string>> examples_subset = filterExamples(examples, decision.test_attribute, possible_value);
        if(examples_subset.empty()){
            string mostCommon = findMostCommon(examples, target_attribute);
            struct node child;
            child.target_value = mostCommon;
            decision.branch.insert({possible_value, child});
        }
        else{
            list<string> newAttributes(attributes);
            newAttributes.erase(find(newAttributes.begin(), newAttributes.end(), decision.test_attribute));
            struct node child = ID3(examples_subset, target_attribute, newAttributes, attribute_values);
            decision.branch.insert({possible_value, child});
        }
    }
    return decision;
}

void show(const struct node& decision, const string& desc){
    if(decision.branch.empty()){
        list<map<string, string>> instances = decision.instances;
        cout << desc;
        for(map<string, string> example : instances){
            cout << example["id"] << " ";
        }
        cout << endl;
        return;
    }
    map<string, struct node> branch = decision.branch;
    for(auto & iter : branch){
        string target_value = iter.first;
        show(iter.second, desc + decision.test_attribute + ": " + target_value + ", ");
    }
}

int main(){
    list<map<string, string>> examples;
    examples.push_back({{"id", "1"}, {"weather", "sunny"}, {"temperature", "hot"}, {"humidity", "high"}, {"wind", "false"}, {"class", "N"}});
    examples.push_back({{"id", "2"},{"weather", "sunny"}, {"temperature", "hot"}, {"humidity", "high"}, {"wind", "true"}, {"class", "N"}});
    examples.push_back({{"id", "3"},{"weather", "cloudy"}, {"temperature", "hot"}, {"humidity", "high"}, {"wind", "false"}, {"class", "P"}});
    examples.push_back({{"id", "4"},{"weather", "rainy"}, {"temperature", "mid"}, {"humidity", "high"}, {"wind", "false"}, {"class", "P"}});
    examples.push_back({{"id", "5"},{"weather", "rainy"}, {"temperature", "cool"}, {"humidity", "mid"}, {"wind", "false"}, {"class", "P"}});
    examples.push_back({{"id", "6"},{"weather", "rainy"}, {"temperature", "cool"}, {"humidity", "mid"}, {"wind", "true"}, {"class", "N"}});
    examples.push_back({{"id", "7"},{"weather", "cloudy"}, {"temperature", "cool"}, {"humidity", "mid"}, {"wind", "true"}, {"class", "P"}});
    examples.push_back({{"id", "8"},{"weather", "sunny"}, {"temperature", "mid"}, {"humidity", "high"}, {"wind", "false"}, {"class", "N"}});
    examples.push_back({{"id", "9"},{"weather", "sunny"}, {"temperature", "cool"}, {"humidity", "mid"}, {"wind", "false"}, {"class", "P"}});
    examples.push_back({{"id", "10"},{"weather", "rainy"}, {"temperature", "mid"}, {"humidity", "mid"}, {"wind", "false"}, {"class", "P"}});
    examples.push_back({{"id", "11"},{"weather", "sunny"}, {"temperature", "mid"}, {"humidity", "mid"}, {"wind", "true"}, {"class", "P"}});
    examples.push_back({{"id", "12"},{"weather", "cloudy"}, {"temperature", "mid"}, {"humidity", "high"}, {"wind", "true"}, {"class", "P"}});
    examples.push_back({{"id", "13"},{"weather", "cloudy"}, {"temperature", "hot"}, {"humidity", "mid"}, {"wind", "false"}, {"class", "P"}});
    examples.push_back({{"id", "14"},{"weather", "rainy"}, {"temperature", "mid"}, {"humidity", "high"}, {"wind", "true"}, {"class", "N"}});

    string target_attribute = "class";
    list<string> attributes;
    attributes.emplace_back("weather");
    attributes.emplace_back("temperature");
    attributes.emplace_back("humidity");
    attributes.emplace_back("wind");
    list<string> weather, temperature, humidity, wind;
    weather.emplace_back("sunny");
    weather.emplace_back("cloudy");
    weather.emplace_back("rainy");
    temperature.emplace_back("hot");
    temperature.emplace_back("mid");
    temperature.emplace_back("cool");
    humidity.emplace_back("high");
    humidity.emplace_back("mid");
    wind.emplace_back("true");
    wind.emplace_back("false");
    map<string, list<string>> attribute_values = {{"weather", weather}, {"temperature", temperature}, {"humidity", humidity}, {"wind", wind}};

    struct node decision = ID3(examples, target_attribute, attributes, attribute_values);
    show(decision, "");

    return 0;
}