#include <string>

namespace graphs{
  class Vertex{
  private:
    /**
     * Each vertex has a name (3 digits until proof of contrary)
     */
    std::string _name;
    int _x;
    int _y;
  public:
    Vertex();
    Vertex(const Vertex & v);
    ~Vertex();

    std::string getName() const;
    int getX() const;
    int getY() const;

    void setName(std::string newName);
    void setPosition(int x, int y);
  };

  std::ostream & operator<<(std::ostream & out, const Vertex & v);
}
