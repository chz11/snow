#include<string>
#include<algorithm>
#include<sstream>
#include "Singleton.h"
namespace base
{
    class ConfigVarBase
    {
    public:
        typedef std::shared_ptr<ConfigVarBase> ConfigVarBasePtr;
        ConfigVarBase(const std::string& name, const std::string& description) : m_name(name), m_description(description)
        {
            std::transform(m_name.begin(),m_name.end(),m_name.begin(), ::tolower);
        }

        const std::string& GetName()
        {
            return m_name;
        }

        const std::string& GetDescription()
        {
            return m_description;
        }

        virtual std::string ToString() = 0;

        virtual bool FromString(const std::string& val) = 0;

        ~ConfigVarBase();
    private:
        std::string m_name;
        std::string m_description;
    };
    
    template<class T>
    class ConfigVal : public ConfigVarBase
    {
    public:
        typedef std::shared_ptr<ConfigVal> ConfigValPtr;
        ConfigVal(const std::string& name, const std::string& description, const T& default_val) : m_val(default_val), ConfigValBase(name, description)
        {

        }

        std::string ToString() override
        {
            try
            {
                ss.clear();
                ss << m_val;
                return ss.str();
            }
            catch(const std::ios_base::failure& e)
            {
                TRACE(LOG_ROOT()) << "exceptions: "<<e.what()<<'\n' << "errorCode: "<< e.code() << '\n';
                return "";
            }           
        }

        bool FromString(const std::string val) override
        {
            try
            {
                ss.clear();
                ss << val;
                ss >> m_val;
                return true;
            }
            catch(const std::ios_base::failure& e)
            {
                TRACE(LOG_ROOT()) << "exceptions: "<<e.what()<<'\n' << "errorCode: "<< e.code() << '\n';
                return false;
            }   
        }

        const T& GetValue ()
        {
            return m_val;
        }

        void SetValue(const T& val)
        {
            m_val = val;
        }
    private:
        T m_val;
        std::stringstream ss;
    };

    class Config
    {
    public:
        typedef std::map<std::string, ConfigVarBase::ConfigVarBasePtr> ConfigMap;
        template<class T>
        static typename ConfigVal<T>::ConfigValPtr Lookup(const std::string& name, const std::string& description, const T& default_val)
        {
            auto temp = Lookup(name);
            if(temp != nullptr)
            {
                TRACE(LOG_ROOT())<<name<<"exists\n";
                return temp;
            }
            if(name.find_first_not_of("abcdefghijklmnopqrstuvwxyz._0123456789") != std::string::npos)
            {
                TRACE(LOG_ROOT())<<name<<" is invalid\n";
                throw std::invalid_argument(name);
            }

            typename ConfigVar<T>::ConfigVarPtr v = std::make_shared<ConfigVal<T> > (name, description, default_val);
            m_configMap[name] = v;
            return v;
        }

        template<class T>
        static typename ConfigVal<T>::ConfigValPtr Lookup(const std::string& name)
        {
            auto temp = m_configMap.find(name);
            if(temp == m_configMap.end())
            {
                return nullptr;
            }
            else
            {
                return dynamic_pointer_cast<ConfigVal<T>::ConfigValPtr>(temp->second());
            }
        }
    private:
        static ConfigMap m_configMap;
    };
    https://github.com/jbeder/yaml-cpp
}