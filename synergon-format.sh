#!/bin/bash

find Samples Engine -regex '.*\.\(cpp\|c\|h\|hpp\)' -exec clang-format -i {} +

echo "Formatting complete!"
