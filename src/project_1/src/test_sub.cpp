#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int64.hpp"

using std::placeholders::_1;

class IncrementalSubscriber : public rclcpp::Node
{
public:
  IncrementalSubscriber()
  : Node("incremental_subscriber")
  {
    // Подписываемся на топик "numbers"
    // <std_msgs::msg::Int64> — тип сообщения
    // 10 — размер очереди (на случай задержек)
    subscription_ = this->create_subscription<std_msgs::msg::Int64>(
      "simple_digit", 10, std::bind(&IncrementalSubscriber::topic_callback, this, _1));
  }

private:
  // Эта функция вызывается каждый раз, когда в топик приходит новое сообщение
  void topic_callback(const std_msgs::msg::Int64::SharedPtr msg) const
  {
    RCLCPP_INFO(this->get_logger(), "нода работает: '%ld'", msg->data);
  }

  rclcpp::Subscription<std_msgs::msg::Int64>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<IncrementalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
