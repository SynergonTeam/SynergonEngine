@echo off
for /r Samples %%f in (*.cpp *.c *.h *.hpp) do (
    clang-format -i "%%f"
)
for /r Engine %%f in (*.cpp *.c *.h *.hpp) do (
    clang-format -i "%%f"
)
echo Formatting complete!
