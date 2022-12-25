namespace base
{
    class Nocopy
    {
    public:
        Nocopy(Nocopy&) = delete;
        Nocopy operator=(Nocopy&) = delete;
    protected:
        Nocopy() = default;
        ~Nocopy() = default;
    };
}