#pragma once

#include <string>

#include <gloperate/gloperate_api.h>

#include <gloperate/pipeline/AbstractData.h>


namespace gloperate 
{

template <typename T>
class TripleBufferedData : public AbstractData
{
public:
    template <typename... Args>
    explicit Data(Args&&... args);

    T & data();
    const T & data() const;

    T & operator*();
    const T & operator*() const;
    T * operator->();
    const T * operator->() const;

    operator const T &() const;

    TripleBufferedData<T> & operator=(const TripleBufferedData<T> & data);
    const T & operator=(const T & value);

    void setData(const T & value);

    virtual std::string type() const override { return typeid(T).name(); }
protected:
    T m_data;
};

} // namespace gloperate


#include <gloperate/pipeline/TripleBufferedData.hpp>
