#pragma once

#include "fmt/format.h"
#include "quill/detail/LogLineInfo.h"
#include "quill/detail/PatternFormatter.h"
#include "quill/detail/message/MessageBase.h"

namespace quill::detail
{

/**
 * Base class for logging sinks
 */
class SinkBase
{
public:
  /**
   * Constructor
   * Uses the default pattern formatter
   */
  SinkBase() = default;

  /**
   * Clone
   * @return
   */
  [[nodiscard]] virtual SinkBase* clone() const = 0;

  /**
   * Constructor
   * Uses a custom formatter
   * @tparam TConstantString
   * @param format_pattern
   */
  template <typename TConstantString>
  explicit SinkBase(TConstantString format_pattern) : _formatter(format_pattern){};

  /**
   * Copy Constructor
   */
  SinkBase(SinkBase const& other) : _formatter(other._formatter){};

  /**
   * Move Constructor
   */
  SinkBase(SinkBase&& other) noexcept : _formatter(std::move(other._formatter)){};

  /**
   * Copy Assignment
   * @return
   */
  SinkBase& operator=(SinkBase const& other)
  {
    if (this != &other)
    {
      _formatter = other._formatter;
    }
    return *this;
  }

  /**
   * Move Assignment
   * @return
   */
  SinkBase& operator=(SinkBase&& other) noexcept
  {
    if (this != &other)
    {
      _formatter = std::move(other._formatter);
    }
    return *this;
  }

  /**
   * Destructor
   */
  virtual ~SinkBase() = default;

  /**
   * Returns the owned formatter by the sink
   * @note: Accessor for backend processing
   * @return
   */
  detail::PatternFormatter const& formatter() { return _formatter; }

  /**
   * Logs the formatted message to the sink
   * @note: Accessor for backend processing
   * @param formatted_line
   */
  virtual void log(fmt::memory_buffer const& formatted_line) = 0;

private:
  detail::PatternFormatter _formatter; /**< Owned formatter for this sink */
};
} // namespace quill::detail