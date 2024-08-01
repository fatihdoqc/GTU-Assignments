template< typename Subject, typename StateTag >
class Observer
{
public:
    virtual ~Observer() = default;
    virtual void update( Subject const& subject, StateTag property ) = 0;
};

class WMSystem
{
public:
    enum StateChange
    {
    TemperatureChanged,
    AirPressureChanged,
    WindChanged
    };

    using SystemObserver = Observer<WMSystem,StateChange>;

    explicit WMSystem( std::string temp, std::string pres , std::string dir , std::string speed )
    : temp_{ std::move(temp) }
    , pres_{ std::move(pres) }
    , dir_{ std::move(dir) }
    , speed_{ std::move(speed) }
    {}

    bool attach( SystemObserver* observer );
    bool detach( SystemObserver* observer );

    void notify( StateChange property );

    void setTemperature(float temp);
    void setAirPressure(float pres);
    void setWind(float dir, float speed);

private:
    std::string temp_;
    std::string pres_;
    std::string dir_;
    std::string speed_;
    std::set<SystemObserver*> observers_;
};

void WMSystem::notify( StateChange property )
{
    for( auto iter=begin(observers_); iter!=end(observers_); )
    {
        auto const pos = iter++;
        (*pos)->update(*this,property);
    }
}

// ------------------------------------------

void WMSystem::setTemperature(float temp){
    temp_ = std::move(temp);
    notify(TemperatureChanged);
}

// same goes for airpressure and wind changes.

class DisplayStation : public Observer<WMSystem>{
    public:
    void displayTemperature(float temp);
    void displayPressure(float pres);
    void displayWind(float dir, float speed);

    void update(WMSystem system, WMSystem::StateChange property);
}

class LogStation : public Observer<WMSystem>{
    public:
    void writeLog(float temp, float pres, float dir, float speed);

    void update(WMSystem system, WMSystem::StateChange property){
        writeLog();
    }
}

int main()
{
    using SystemObserver = Observer<WMSystem,WMSystem::StateChange>;

    SystemObserver Observer( StateChange );

    WMSystem sys();

    // Attaching observers
    sys.attach( &SystemObserver );
 
    return EXIT_SUCCESS;
}