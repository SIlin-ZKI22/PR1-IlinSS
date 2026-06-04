#include "pch.h"
#include "CppUnitTest.h"
#include "Transport.h"
#include "TransportContainer.h"
#include "FileCommandReader.h"
#include "constants.h"
#include <fstream>
#include <filesystem>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Constants;

namespace TransportManagerTests
{
    // Класс 1: Тесты моделей транспорта
    TEST_CLASS(TransportModelTests)
    {
    public:
        TEST_METHOD(CreateValidPlane_InitializesCorrectly)
        {
            Plane plane(500, 10, "Ivanov", 800, 1000);

            Assert::AreEqual(500, plane.getSpeed());
            Assert::AreEqual(10, plane.getDistance());
            Assert::AreEqual(std::string("Ivanov"), plane.getOwner());
        }

        TEST_METHOD(CreateValidTrain_InitializesCorrectly)
        {
            Train train(120, 600, "Petrov", 15);

            Assert::AreEqual(120, train.getSpeed());
            Assert::AreEqual(600, train.getDistance());
            Assert::AreEqual(std::string("Petrov"), train.getOwner());
        }

        TEST_METHOD(CreateValidTruck_InitializesCorrectly)
        {
            Truck truck(90, 300, "Sidorov", 5000, 12.5);

            Assert::AreEqual(90, truck.getSpeed());
            Assert::AreEqual(300, truck.getDistance());
            Assert::AreEqual(std::string("Sidorov"), truck.getOwner());
        }

        TEST_METHOD(NegativeSpeed_ThrowsInvalidArgument)
        {
            auto func = []() {
                Plane plane(-500, 10, "Ivanov", 800, 1000);
                };
            Assert::ExpectException<std::invalid_argument>(func);
        }

        TEST_METHOD(NegativeDistance_ThrowsInvalidArgument)
        {
            auto func = []() {
                Train train(120, -600, "Petrov", 15);
                };
            Assert::ExpectException<std::invalid_argument>(func);
        }

        TEST_METHOD(EmptyOwner_ThrowsInvalidArgument)
        {
            auto func = []() {
                Truck truck(90, 300, "", 5000, 12.5);
                };
            Assert::ExpectException<std::invalid_argument>(func);
        }
    };

    // Класс 2: Тесты контейнера
    TEST_CLASS(ContainerTests)
    {
    public:
        TEST_METHOD(Add_Plane_IncreasesContainerSize)
        {
            TransportContainer container;
            container.add(new Plane(500, 10, "Ivanov", 800, 1000));

            Assert::AreEqual(1, (int)container.getSize());
        }

        TEST_METHOD(Add_MultipleVehicles_IncreasesSize)
        {
            TransportContainer container;
            container.add(new Plane(500, 10, "Ivanov", 800, 1000));
            container.add(new Train(120, 600, "Petrov", 15));
            container.add(new Truck(90, 300, "Sidorov", 5000, 12.5));

            Assert::AreEqual(3, (int)container.getSize());
        }

        TEST_METHOD(Remove_BySpeedGreaterThan_RemovesCorrectly)
        {
            TransportContainer container;
            container.add(new Plane(500, 10, "Ivanov", 800, 1000));
            container.add(new Train(120, 600, "Petrov", 15));
            container.add(new Truck(90, 300, "Sidorov", 5000, 12.5));

            container.remove(SPEED_RU + " > 100");

            Assert::AreEqual(1, (int)container.getSize());
        }

        TEST_METHOD(Remove_ByDistanceLessThan_RemovesCorrectly)
        {
            TransportContainer container;
            container.add(new Plane(500, 10, "Ivanov", 800, 1000));
            container.add(new Train(120, 600, "Petrov", 15));
            container.add(new Truck(90, 300, "Sidorov", 5000, 12.5));

            container.remove(DISTANCE_RU + " < 500");

            Assert::AreEqual(1, (int)container.getSize());
        }

        TEST_METHOD(Remove_ByOwnerEquals_RemovesCorrectly)
        {
            TransportContainer container;
            container.add(new Plane(500, 10, "Ivanov", 800, 1000));
            container.add(new Train(120, 600, "Petrov", 15));
            container.add(new Truck(90, 300, "Sidorov", 5000, 12.5));

            container.remove(OWNER_RU + " = Petrov");

            Assert::AreEqual(2, (int)container.getSize());
        }

        TEST_METHOD(Remove_EmptyContainer_DoesNotThrow)
        {
            TransportContainer container;

            
            container.remove(SPEED_RU + " > 100");

            
            Assert::AreEqual(0, (int)container.getSize());
        }

        TEST_METHOD(Remove_UnknownField_DoesNotThrow)
        {
            TransportContainer container;
            container.add(new Plane(500, 10, "Ivanov", 800, 1000));

            container.remove(SPEED_RU + " > 100");
            Assert::AreEqual(0, (int)container.getSize());
        }

        TEST_METHOD(Remove_InvalidNumber_DoesNotThrow)
        {
            TransportContainer container;
            container.add(new Plane(500, 10, "Ivanov", 800, 1000));

            container.remove("неизвестное_поле > 100");
            Assert::AreEqual(1, (int)container.getSize());
        }
    };

    // Класс 3: Тесты чтения команд из файла
    TEST_CLASS(FileCommandReaderTests)
    {
    public:
        TEST_METHOD(ReadAndExecute_ValidFile_ProcessesCommands)
        {
            std::ofstream testFile("test_commands.txt");
            testFile << "ADD Plane 500 10 Ivanov 800 1000\n";
            testFile << "PRINT\n";
            testFile.close();

            TransportContainer container;
            FileCommandReader reader("test_commands.txt");

            reader.readAndExecute(container);

            Assert::AreEqual(1, (int)container.getSize());

            std::remove("test_commands.txt");
        }

        TEST_METHOD(ReadAndExecute_FileNotFound_DoesNotThrow)
        {
            TransportContainer container;
            FileCommandReader reader("non_existent_file.txt");

            reader.readAndExecute(container);

            Assert::AreEqual(0, (int)container.getSize());
        }

        TEST_METHOD(ReadAndExecute_EmptyFile_DoesNotThrow)
        {
            std::ofstream testFile("empty_commands.txt");
            testFile.close();

            TransportContainer container;
            FileCommandReader reader("empty_commands.txt");

            reader.readAndExecute(container);

            Assert::AreEqual(0, (int)container.getSize());

            std::remove("empty_commands.txt");
        }

        TEST_METHOD(ReadAndExecute_InvalidCommand_DoesNotThrow)
        {
            std::ofstream testFile("invalid_commands.txt");
            testFile << "UNKNOWN\n";
            testFile.close();

            TransportContainer container;
            FileCommandReader reader("invalid_commands.txt");

            reader.readAndExecute(container);

            std::remove("invalid_commands.txt");
        }
    };

    // Класс 4: Тесты парсинга условий
    TEST_CLASS(ConditionParserTests)
    {
    public:
        TEST_METHOD(ParseSpeedCondition_Greater_ReturnsTrue)
        {
            TransportContainer container;
            container.add(new Plane(500, 10, "Ivanov", 800, 1000));

            container.remove(SPEED_RU + " > 100");

            Assert::AreEqual(0, (int)container.getSize());
        }

        TEST_METHOD(ParseSpeedCondition_Less_ReturnsTrue)
        {
            TransportContainer container;
            container.add(new Truck(90, 300, "Sidorov", 5000, 12.5));

            container.remove(SPEED_RU + " < 100");

            Assert::AreEqual(0, (int)container.getSize());
        }

        TEST_METHOD(ParseDistanceCondition_Greater_ReturnsTrue)
        {
            TransportContainer container;
            container.add(new Train(120, 600, "Petrov", 15));

            container.remove(DISTANCE_RU + " > 500");

            Assert::AreEqual(0, (int)container.getSize());
        }

        TEST_METHOD(ParseOwnerCondition_Equal_ReturnsTrue)
        {
            TransportContainer container;
            container.add(new Train(120, 600, "Petrov", 15));

            container.remove(OWNER_RU + " = Petrov");

            Assert::AreEqual(0, (int)container.getSize());
        }

        TEST_METHOD(ParseRussianFieldNames_WorksCorrectly)
        {
            TransportContainer container;
            container.add(new Plane(500, 10, "Ivanov", 800, 1000));

            container.remove("скорость > 100");

            Assert::AreEqual(0, (int)container.getSize());
        }

        TEST_METHOD(ParseEnglishFieldNames_WorksCorrectly)
        {
            TransportContainer container;
            container.add(new Plane(500, 10, "Ivanov", 800, 1000));

            container.remove("speed > 100");

            Assert::AreEqual(0, (int)container.getSize());
        }

        TEST_METHOD(ParseInvalidOperator_DoesNotDelete)
        {
            TransportContainer container;
            container.add(new Plane(500, 10, "Ivanov", 800, 1000));

            container.remove(SPEED_RU + " % 100");

            Assert::AreEqual(1, (int)container.getSize());
        }
    };
}