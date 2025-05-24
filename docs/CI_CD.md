# CI/CD Pipeline for ESP32-C3 OLED Project

This document describes the GitHub Actions CI/CD pipeline set up for this ESP32-C3 OLED project.

## Overview

The pipeline automatically builds and tests the project whenever code is pushed to the main branches or when pull requests are created.

## Workflow Structure

### Build Job
- **Triggers**: Push to `main`, `master`, or `develop` branches, and pull requests
- **Environment**: Ubuntu latest
- **Steps**:
  1. Checkout the code
  2. Set up Python environment
  3. Cache PlatformIO dependencies for faster builds
  4. Install PlatformIO Core
  5. Build the main project (`esp32-c3` environment)
  6. Build the test environment (`esp32-c3-test` environment)
  7. Run unit tests
  8. Run static analysis (optional, continues on error)
  9. Upload firmware artifacts

### Code Quality Job
- **Runs in parallel** with the build job
- **Steps**:
  1. Checkout the code
  2. Set up Python environment
  3. Install PlatformIO Core
  4. Check code formatting (if `.clang-format` exists)
  5. Run PlatformIO static analysis

## Project Configuration

### PlatformIO Environments

1. **esp32-c3**: Main build environment for the ESP32-C3 target
2. **esp32-c3-test**: Test environment with Unity testing framework enabled

### Testing

- **Framework**: Unity (PlatformIO's built-in testing framework)
- **Test location**: `test/test_main.cpp`
- **Test types**: Unit tests for basic functionality

## Local Development

### Running Tests Locally

```bash
# Build the project
pio run --environment esp32-c3

# Build and run tests
pio test --environment esp32-c3-test

# Run static analysis
pio check
```

### Adding New Tests

1. Create test files in the `test/` directory
2. Follow Unity testing framework conventions
3. Include necessary headers and test functions
4. Update the test environment if needed

## Artifacts

The pipeline generates firmware artifacts that are stored for 30 days:
- Main firmware binary
- Test firmware binary

## Customization

### Adding More Environments

To add more build targets, add new environment sections in `platformio.ini`:

```ini
[env:new-board]
platform = espressif32
board = your-board-name
framework = arduino
lib_deps = 
    olikraus/U8g2 @ ^2.35.9
```

Then update the GitHub Actions workflow to build the new environment.

### Code Formatting

To enable automatic code formatting checks:
1. Add a `.clang-format` file to the project root
2. The pipeline will automatically check formatting compliance

### Extending Tests

For more comprehensive testing:
1. Add hardware-in-the-loop tests
2. Create mock objects for hardware components
3. Add integration tests for OLED functionality
4. Test animation sequences and timing

## Troubleshooting

### Common Issues

1. **Build failures**: Check PlatformIO configuration and dependencies
2. **Test failures**: Verify test logic and Unity framework usage
3. **Static analysis warnings**: Review code quality suggestions

### Debug Options

- Enable verbose output in workflow
- Check artifact uploads for firmware binaries
- Review PlatformIO check results for code quality issues

## Future Enhancements

- Add hardware simulation testing
- Implement automated releases with semantic versioning
- Add coverage reporting
- Include performance benchmarks 