
namespace lasd {

/* ************************************************************************** */

    // --------------- NODE ----------------

    // Specific constructors
    template <typename Data>
    List<Data>::Node::Node(Data &&dat) noexcept {
        std::swap(element, dat);
    }

    // Move constructor
    template <typename Data>
    List<Data>::Node::Node(Node &&node) noexcept {
        std::swap(element, node.element);
        std::swap(next, node.next);
    }

    // Destructor
    template <typename Data>
    List<Data>::Node::~Node(){
        delete next;
    }

    // Comparison operators
    template <typename Data>
    bool List<Data>::Node::operator==(const Node &node) const noexcept {
        return (element == node.element) \ 
        && ((next == nullptr && node.next == nullptr) || (next != null && node.next != null));
    }

    inline bool operator!=(const Node &node) const noexcept {
        return !(*this == node);
    }

/* ************************************************************************** */

}
