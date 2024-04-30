#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/vector3.hpp"
#include <memory>
#include <chrono>
#include <functional>

using namespace std::chrono_literals;

void callback(rclcpp::Node::SharedPtr node, rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr pub)
{
    auto message = geometry_msgs::msg::Vector3();
    RCLCPP_INFO(node->get_logger(), "Please input x, y, z: ");
    std::cin >> message.x >> message.y >> message.z;
    RCLCPP_INFO(node->get_logger(), "Publish: x: %lf, y: %lf, z: %lf", message.x, message.y, message.z);
    pub->publish(message);
}

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("pub2_2");
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    auto pub = node->create_publisher<geometry_msgs::msg::Vector3>("/pub2_2", qos_profile);
    std::function<void()> fn = std::bind(callback, node, pub);
    auto timer = node->create_wall_timer(100ms, fn);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}