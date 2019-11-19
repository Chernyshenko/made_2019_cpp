#pragma once
#include <ostream>
#include <istream>
enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer
{
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream& out)
        : out_(out)
    {
    }

    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args)
    {
        return process(std::forward<ArgsT>(args)...);
    }
    
private:
    std::ostream& out_;

    Error process(bool val){
        if (val) out_ << "true" << Separator;
        else out_ << "false" << Separator;
        return Error::NoError;
    }
    template <class T>
    Error process(T&& val){
        out_ << val << Separator;
        return Error::NoError;
    }
    template <class T, class... Args>
    Error process(T&& val, Args&&... args)
    {
        process(std::forward<T>(val));
        process(std::forward<Args>(args)...);
        return Error::NoError;
    }
};


class Deserializer
{
public:
    explicit Deserializer(std::istream& in)
        : in_(in)
    {
    }

    template <class T>
    Error load(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args)
    {
        return deprocess(std::forward<ArgsT>(args)...);
    }
    
private:
    std::istream& in_;

    Error deprocess(bool& value){
        std::string text;
        in_ >> text;

        if (text == "true")
            value = true;
        else if (text == "false")
            value = false;
        else
            return Error::CorruptedArchive;

        return Error::NoError;
    }
    template <class T> //int
    Error deprocess(T&& value){
        in_ >> value;
        return Error::NoError;
    }
    template <class T, class... Args>
    Error deprocess(T&& val, Args&&... args)
    {
        deprocess(std::forward<T>(val));
        deprocess(std::forward<Args>(args)...);
        return Error::NoError;
    }
};


