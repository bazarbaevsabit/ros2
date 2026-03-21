#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int64.hpp"

using namespace std::chrono_literals;

class IncrementalPublisher : public rclcpp::Node
{
public:
  IncrementalPublisher():
  Node("incremental_publisher"), count_(1)
  {
    // Создаем издателя в топик "numbers" с очередью 10
    publisher_ = this->create_publisher<std_msgs::msg::Int64>("simple_digit", 10);

    // Таймер срабатывает каждую 1 секунду
    timer_ = this->create_wall_timer(
      1s, std::bind(&IncrementalPublisher::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto message = std_msgs::msg::Int64();
    message.data = count_++;
    
    RCLCPP_INFO(this->get_logger(), "Нода публикует: '%ld'", message.data);
    publisher_->publish(message);
  }

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::Int64>::SharedPtr publisher_;
  int64_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<IncrementalPublisher>());
  rclcpp::shutdown();
  return 0;
}
