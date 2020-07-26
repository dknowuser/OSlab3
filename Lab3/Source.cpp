#include <Windows.h>
#include <iostream>

int main(void)
{
	setlocale(LC_ALL, "Russian");
	char InputChar = '\0';

	while (InputChar != '0')
	{
		std::cout << std::endl << "����:" << std::endl << std::endl;
		std::cout << "1 - ����� ������ ������;" << std::endl;
		std::cout << "2 - ��� ������ �� ��������� ������ ����� ���������� � ����� � ������ ���������� ������������;" << std::endl;
		std::cout << "3 - �������� � �������� �������� ���������;" << std::endl;
		std::cout << "4 - �������� ������;" << std::endl;
		std::cout << "5 - ����������� � ����������� ������ ����� ���������� � ������������ ���������\n������� ������ � �������, �������� ����������� �����;" << std::endl;
		std::cout << "6 - ������ � ��������� ��������� ������;" << std::endl;
		std::cout << "0 - �����;" << std::endl;
		std::cout << ">> ";

		std::cin >> InputChar;

		int SomeTemp = 0;
		int Counter = 0;
	    char *DiskName = new char[80];
		bool ErrorOccured = false;
		wchar_t* wcDiskName = new wchar_t[80];
		char *cPath = new char[256];
		wchar_t* mPath = new wchar_t[256];
		char *cPath1 = new char[256];
		wchar_t* mPath1 = new wchar_t[256];

		LPTSTR lpVolumeNameBufferm;
		DWORD *lpVolumeSerialNumberm;
		DWORD *lpMaximumComponentLengthm;
		DWORD *lpFileSystemFlagsm;
		wchar_t  *lpFileSystemNameBufferm;

		DWORD *lpSectorsPerClusterm;
		DWORD *lpBytesPerSector;
		DWORD *lpNumberOfFreeClusters;
		DWORD *lpTotalNumberOfClusters;

		switch (InputChar)
		{
		case '1':
			std::cout << "������ ������:" << std::endl;
			SomeTemp = GetLogicalDrives();

			//� ����� �������� �� ���� ����� ����������� ����� � ������� ��������� �����
			Counter = 0;
			while (SomeTemp)
			{
				if (SomeTemp & 1)
				{
					std::cout << (char)(65 + Counter) << ' ';
				};

				SomeTemp >>= 1;
				Counter++;
			};

			break;
		case '2':
			std::cout << "������� ��� �����, � ������� ����� ������� ����������: ";
			std::cin >> DiskName;
			mbstowcs_s(NULL, wcDiskName, 80, DiskName, _TRUNCATE);

			//���������� ��� �����
			switch (GetDriveType(wcDiskName))
			{
			case 0:
				std::cout << "������! ��� ����� �� ����� ���� ��������." << std::endl;
				ErrorOccured = true;
				break;
			case 1:
				std::cout << "������! ���� �������." << std::endl;
				ErrorOccured = true;
				break;
			case 2:
				std::cout << DiskName << " - ������� ����." << std::endl;
				break;
			case 3: 
				std::cout << DiskName << " - ������ ����." << std::endl;
				break;
			case 4:
				std::cout << DiskName << " - ������� ����." << std::endl;
				break;
			case 5:
				std::cout << DiskName << " - CD-ROM." << std::endl;
				break;
			case 6:
				std::cout << DiskName << " - RAM-����." << std::endl;
				break;
			default:
				std::cout << "����������� ������." << std::endl;
				ErrorOccured = true;
				break;
			};

			if (ErrorOccured)
				break;

			//������� ���������� � �����
			lpVolumeNameBufferm = new wchar_t[MAX_PATH + 1];
			lpVolumeSerialNumberm = new DWORD;
			lpMaximumComponentLengthm = new DWORD;
			lpFileSystemFlagsm = new DWORD;
			lpFileSystemNameBufferm = new wchar_t[MAX_PATH + 1];

			if (!GetVolumeInformation(wcDiskName, lpVolumeNameBufferm, MAX_PATH + 1, lpVolumeSerialNumberm, lpMaximumComponentLengthm, lpFileSystemFlagsm, lpFileSystemNameBufferm, MAX_PATH + 1))
			{
				std::cout << "����������� ������." << std::endl;
				ErrorOccured = true;
			}
			else
			{
				//������� ��� �����
				std::cout << "��� �����: ";
				char *ptr = (char*)lpVolumeNameBufferm;
				while (*ptr)
				{
					std::cout << *ptr;
					ptr++; ptr++;
				};
				std::cout << std::endl;

				//������� �������� ����� �����
				std::cout << "�������� ����� �����: " << *lpVolumeSerialNumberm << std::endl;

				//������� ������������ ����� ����� �����
				std::cout << "������������ ����� ����� �����: " << *lpMaximumComponentLengthm << std::endl;

				//������� �����, ��������� � �������� ��������
				if (*lpFileSystemFlagsm & 0x00000001)
					std::cout << "��������� ��� ������ � ������ ��������." << std::endl;

				if (*lpFileSystemFlagsm & 0x00000002)
					std::cout << "��������� ����������� �������� ��� ������ ��� ���������� �� �����." << std::endl;
				
				if (*lpFileSystemFlagsm & 0x20000000)
					std::cout << "��� ������� ������� (DAX)." << std::endl;

				if (*lpFileSystemFlagsm & 0x00000010)
					std::cout << "��������� ������ �� ������ ������." << std::endl;

				if (*lpFileSystemFlagsm & 0x00040000)
					std::cout << "��������� ����������� �������." << std::endl;

				if (*lpFileSystemFlagsm & 0x00000008)
					std::cout << "��������� ���������� � ���������� ������� ���������� �������� (ACL)." << std::endl;

				if (*lpFileSystemFlagsm & 0x00080000)
					std::cout << "������ ��� ������." << std::endl;

				if (*lpFileSystemFlagsm & 0x00100000)
					std::cout << "��������� ����� ���������������� ������." << std::endl;

				if (*lpFileSystemFlagsm & 0x00020000)
					std::cout << "��������� ������������� �������� ������� (EFS)." << std::endl;

				if (*lpFileSystemFlagsm & 0x00800000)
					std::cout << "��������� ����������� ���������." << std::endl;

				if (*lpFileSystemFlagsm & 0x00400000)
					std::cout << "��������� ������ ������." << std::endl;

				if (*lpFileSystemFlagsm & 0x00010000)
					std::cout << "��������� ��������������� ��������." << std::endl;

				if (*lpFileSystemFlagsm & 0x01000000)
					std::cout << "��������� �������� �� �������������� �����." << std::endl;

				if (*lpFileSystemFlagsm & 0x00000080)
					std::cout << "��������� ����� ��������� ���������." << std::endl;

				if (*lpFileSystemFlagsm & 0x00000040)
					std::cout << "��������� ����������� ������." << std::endl;

				if (*lpFileSystemFlagsm & 0x00200000)
					std::cout << "��������� ����������." << std::endl;

				if (*lpFileSystemFlagsm & 0x02000000)
					std::cout << "��������� �������� ����������� ������ ���������� (USN)." << std::endl;

				if (*lpFileSystemFlagsm & 0x00000004)
					std::cout << "��������� Unicode � ������ ������ �� ���� �� ��������� �� �����." << std::endl;

				if (*lpFileSystemFlagsm & 0x00008000)
					std::cout << "������ ����." << std::endl;

				if (*lpFileSystemFlagsm & 0x00000020)
					std::cout << "��������� �������� ����." << std::endl;

				//������� ��� �������� �������
				std::cout << "��� �������� �������: ";
				ptr = (char*)lpFileSystemNameBufferm;
				while (*ptr)
				{
					std::cout << *ptr;
					ptr++; ptr++;
				};
				std::cout << std::endl;
			};

			delete[] lpFileSystemNameBufferm;
			delete lpFileSystemFlagsm;
			delete lpMaximumComponentLengthm;
			delete lpVolumeSerialNumberm;
			delete[] lpVolumeNameBufferm;

			if (ErrorOccured)
				break;

			//�������� ������ ���������� ������������ �� �����
			lpSectorsPerClusterm = new DWORD;
			lpBytesPerSector = new DWORD;
			lpNumberOfFreeClusters = new DWORD;
			lpTotalNumberOfClusters = new DWORD;

			if (!GetDiskFreeSpace(wcDiskName, lpSectorsPerClusterm, lpBytesPerSector, lpNumberOfFreeClusters, lpTotalNumberOfClusters))
			{
				std::cout << "����������� ������." << std::endl;
				ErrorOccured = true;
			}
			else
			{
				std::cout << "����� �������� � ��������: " << *lpSectorsPerClusterm << std::endl;
				std::cout << "���� � �������: " << *lpBytesPerSector << std::endl;
				std::cout << "����� ��������� ���������: " << *lpNumberOfFreeClusters << std::endl;
				std::cout << "����� ����� ���������: " << *lpTotalNumberOfClusters << std::endl;
			};

			delete lpSectorsPerClusterm;
			delete lpBytesPerSector;
			delete lpNumberOfFreeClusters;
			delete lpTotalNumberOfClusters;

			break;
		case '3':
			InputChar = '0';
			std::cout << "������� \'c\', ����� ������� �������, ��� \'d\', ����� ������� �������: ";
			std::cin >> InputChar;

			if ((InputChar == 'c') || (InputChar == 'C'))
			{
				std::cout << "������� ��� ������������ ��������:" << std::endl;
				std::cin >> cPath;
				mbstowcs_s(NULL, mPath, 256, cPath, _TRUNCATE);

				if (!CreateDirectory(mPath, NULL))
					std::cout << "������ ��� �������� �������� \'" << cPath << "\"" << std::endl;
				else
					std::cout << "������� \"" << cPath << "\" ������� ������." << std::endl;
			}
			else
			{
				if ((InputChar == 'd') || (InputChar == 'D'))
				{
					std::cout << "������� ��� ���������� ��������:" << std::endl;
					std::cin >> cPath;
					mbstowcs_s(NULL, mPath, 256, cPath, _TRUNCATE);

					if (!RemoveDirectory(mPath))
						std::cout << "������ ��� �������� �������� \"" << cPath << "\"." << std::endl;
					else
						std::cout << "������� \"" << cPath << "\" ������� �����." << std::endl;
				}
				else
				{
					std::cout << "������! ����� �������� �������� ��� ������ ��������." << std::endl;
					std::cin.clear();
					std::cin.sync();
					break;
				};
			};

			break;
		case '4':
			std::cout << "������� ��� �����, ������� ����� �������:" << std::endl;
			std::cin >> cPath;
			mbstowcs_s(NULL, mPath, 256, cPath, _TRUNCATE);

			if(CreateFile(mPath, GENERIC_WRITE, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL) == INVALID_HANDLE_VALUE)
				std::cout << "������ ��� �������� ����� \"" << cPath << "\"." << std::endl;
			else
				std::cout << "���� \"" << cPath << "\" ������� ������." << std::endl;
			break;
		case '5':
			InputChar = '0';
			std::cout << "������� \'c\', ����� ����������� ����, ��� \'m\', ����� ����������� ����: ";
			std::cin >> InputChar;

			if ((InputChar == 'c') || (InputChar == 'C'))
			{
				std::cout << "������� ��� �����, ������� ����� �����������:" << std::endl;
				std::cin >> cPath;
				mbstowcs_s(NULL, mPath, 256, cPath, _TRUNCATE);

				std::cout << "������� ��� ������ �����:" << std::endl;
				std::cin >> cPath1;
				mbstowcs_s(NULL, mPath1, 256, cPath1, _TRUNCATE);

				if (CopyFile(mPath, mPath1, TRUE))
					std::cout << "���� \"" << cPath << "\" ������� ���������� � ���� \"" << cPath1 << "\"." << std::endl;
				else
					std::cout << "������ ��� ����������� ����� \"" << cPath << "\" � ���� \"" << cPath1 << "\"\n - ����������� ����� ������." << std::endl;
			}
			else
			{
				if ((InputChar == 'm') || (InputChar == 'M'))
				{
					std::cout << "������� ��� �����, ������� ����� �����������:" << std::endl;
					std::cin >> cPath;
					mbstowcs_s(NULL, mPath, 256, cPath, _TRUNCATE);

					std::cout << "������� ����, ���� ����� ����������� ����:" << std::endl;
					std::cin >> cPath1;
					mbstowcs_s(NULL, mPath1, 256, cPath1, _TRUNCATE);

					if (MoveFile(mPath, mPath1))
						std::cout << "���� \"" << cPath << "\" ������� ��������� �� ���� \"" << cPath1 << "\"." << std::endl;
					else
						std::cout << "������ ��� ����������� ����� \"" << cPath << "\" �� ���� \"" << cPath1 << "\"\n - ����������� ����� ������." << std::endl;
				}
				else
				{
					std::cout << "������! ����� �������� �������� ��� ������ ��������." << std::endl;
					std::cin.clear();
					std::cin.sync();
					break;
				};
			};

			break;
		case '6':
			InputChar = '0';
			std::cout << "������� \'g\', ����� �������� �������� �����,\n��� \'s\', ����� ���������� �������� �����: ";
			std::cin >> InputChar;

			if ((InputChar == 'g') || (InputChar == 'G'))
			{
				std::cout << "������� ��� �����, �������� �������� ����� ��������:" << std::endl;
				std::cin >> cPath;
				mbstowcs_s(NULL, mPath, 256, cPath, _TRUNCATE);

				DWORD dwTemp = GetFileAttributes(mPath);
				if (dwTemp == INVALID_FILE_ATTRIBUTES)
				{
					std::cout << "������ ��� ��������� ��������� ����� \"" << cPath << "\"." << std::endl;
					break;
				};

				//������� �������� �����
				if(dwTemp & 0x20)
					std::cout << "�������� ���� ��� �������." << std::endl;

				if (dwTemp & 0x800)
					std::cout << "������ ���� ��� �������." << std::endl;

				if (dwTemp & 0x10)
					std::cout << "����������, ���������������� �������." << std::endl;

				if (dwTemp & 0x4000)
					std::cout << "������������� ���� ��� �������." << std::endl;

				if (dwTemp & 0x2)
					std::cout << "������� ���� ��� �������." << std::endl;

				if (dwTemp & 0x8000)
					std::cout << "������� ��� ����� ������ ������������ �������� �� �����������." << std::endl;

				if (dwTemp & 0x80)
					std::cout << "����, � �������� ��� ������ ���������." << std::endl;

				if (dwTemp & 0x2000)
					std::cout << "���� ��� ������� �� ��������������� ������� ��������������." << std::endl;

				if (dwTemp & 0x20000)
					std::cout << "���������������� ����� ������ �� ������� ������ � ������� ������ ����������� ������." << std::endl;

				if (dwTemp & 0x1000)
					std::cout << "������ ����� ���������� ����� (������ ����� ��������� ������������ � ���������� ���������)." << std::endl;

				if (dwTemp & 0x1)
					std::cout << "���� ������ ��� ������." << std::endl;

				if (dwTemp & 0x400000)
					std::cout << "���� ��� ������� �� ��������� ������������ ��������." << std::endl;

				if (dwTemp & 0x40000)
					std::cout << "���� ��� ������� �� ����� ����������� ������������� � ��������� �������; ������� �������� �����������." << std::endl;

				if (dwTemp & 0x400)
					std::cout << "���� ��� �������, ������� ��������� ����� ��������� ���������, ��� ����, ���������� ������������� �������." << std::endl;

				if (dwTemp & 0x200)
					std::cout << "����������� ����." << std::endl;

				if (dwTemp & 0x4)
					std::cout << "���� ��� �������, ������� ������������ ������� ���������� �������������, ��� ���� ��� �������, � ������� ������������ ������� ���������� �����." << std::endl;

				if (dwTemp & 0x100)
					std::cout << "����, ������������ ��� ���������� ��������." << std::endl;

				std::cout << std::endl;

				HANDLE hdl = CreateFile(mPath, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				BY_HANDLE_FILE_INFORMATION FileInfo;
				SYSTEMTIME SysTime;
				if (!GetFileInformationByHandle(hdl, &FileInfo))
				{
					std::cout << "������ ��� ��������� ��������� ����� \"" << cPath << "\"." << std::endl;
					break;
				};

				//������� ������ � �����
				if (!FileTimeToSystemTime(&FileInfo.ftCreationTime, &SysTime))
					std::cout << "������ ��� ��������� ������� �������� ����� \"" << cPath << "\"." << std::endl;

				std::cout << "����� �������� �����:\n����: " << SysTime.wDay << '.' << SysTime.wMonth << '.' << SysTime.wYear << "\n�����: " << SysTime.wHour << ':' << SysTime.wMinute
					<< ':' << SysTime.wSecond << ':' << SysTime.wMilliseconds << "\n���� ������: " << SysTime.wDayOfWeek << std::endl << std::endl;

				if (!FileTimeToSystemTime(&FileInfo.ftLastAccessTime, &SysTime))
					std::cout << "������ ��� ��������� ������� ���������� ������� � ����� \"" << cPath << "\"." << std::endl;

				std::cout << "����� ���������� ������� � �����:\n����: " << SysTime.wDay << '.' << SysTime.wMonth << '.' << SysTime.wYear << "\n�����: " << SysTime.wHour << ':' << SysTime.wMinute
					<< ':' << SysTime.wSecond << ':' << SysTime.wMilliseconds << "\n���� ������: " << SysTime.wDayOfWeek << std::endl << std::endl;

				if (!FileTimeToSystemTime(&FileInfo.ftLastWriteTime, &SysTime))
					std::cout << "������ ��� ��������� ������� ��������� ������ � ���� \"" << cPath << "\"." << std::endl;

				std::cout << "����� ��������� ������ � ����:\n����: " << SysTime.wDay << '.' << SysTime.wMonth << '.' << SysTime.wYear << "\n�����: " << SysTime.wHour << ':' << SysTime.wMinute
					<< ':' << SysTime.wSecond << ':' << SysTime.wMilliseconds << "\n���� ������: " << SysTime.wDayOfWeek << std::endl << std::endl;

				std::cout << "�������� ����� �����, ������� �������� ����: " << FileInfo.dwVolumeSerialNumber << std::endl;
				std::cout << "������ �����: " << FileInfo.nFileSizeLow + (FileInfo.nFileSizeHigh << 32) << std::endl;
				std::cout << "����� ������ �� ����: " << FileInfo.nNumberOfLinks << std::endl;
				std::cout << "���������� �������������, ��������������� � ������: " << FileInfo.nFileIndexLow + (FileInfo.nFileIndexHigh << 32) << std::endl;
			}
			else
			{
				if ((InputChar == 's') || (InputChar == 'S'))
				{
					std::cout << "������� ��� �����, �������� �������� ����� ��������:" << std::endl;
					std::cin >> cPath;
					mbstowcs_s(NULL, mPath, 256, cPath, _TRUNCATE);

					DWORD dwTemp;
					std::cout << "������� �������� �����: ";
					std::cin >> dwTemp;

					if(SetFileAttributes(mPath, dwTemp))
						std::cout << "�������� ����� \"" << cPath << "\" ������� ��������." << std::endl;
					else
					{
						std::cout << "������ ��� ��������� ��������� ����� \"" << cPath << "\"." << std::endl;
						break;
					};

					HANDLE hdl = CreateFile(mPath, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
					BY_HANDLE_FILE_INFORMATION FileInfo;
					SYSTEMTIME SysTime;

					//����� �������� �����
					std::cout << "������� ���� �������� �����: ";
					std::cin >> SysTime.wDay;

					std::cout << "������� ����� �������� �����: ";
					std::cin >> SysTime.wMonth;

					std::cout << "������� ��� �������� �����: ";
					std::cin >> SysTime.wYear;

					std::cout << "������� ��� �������� �����: ";
					std::cin >> SysTime.wHour;

					std::cout << "������� ������ �������� �����: ";
					std::cin >> SysTime.wMinute;

					std::cout << "������� ������� �������� �����: ";
					std::cin >> SysTime.wSecond;

					std::cout << "������� ������������ �������� �����: ";
					std::cin >> SysTime.wMilliseconds;

					std::cout << "������� ���� ������ �������� �����: ";
					std::cin >> SysTime.wDayOfWeek;

					if (!SystemTimeToFileTime(&SysTime, &FileInfo.ftCreationTime))
					{
						std::cout << "������ ��� ��������� ������� �������� ����� \"" << cPath << "\"." << std::endl;
						break;
					};

					//����� ���������� ������� � �����
					std::cout << "������� ���� ���������� ������� � �����: ";
					std::cin >> SysTime.wDay;

					std::cout << "������� ����� ���������� ������� � �����: ";
					std::cin >> SysTime.wMonth;

					std::cout << "������� ��� ���������� ������� � �����: ";
					std::cin >> SysTime.wYear;

					std::cout << "������� ��� ���������� ������� � �����: ";
					std::cin >> SysTime.wHour;

					std::cout << "������� ������ ���������� ������� � �����: ";
					std::cin >> SysTime.wMinute;

					std::cout << "������� ������� ���������� ������� � �����: ";
					std::cin >> SysTime.wSecond;

					std::cout << "������� ������������ ���������� ������� � �����: ";
					std::cin >> SysTime.wMilliseconds;

					std::cout << "������� ���� ������ ���������� ������� � �����: ";
					std::cin >> SysTime.wDayOfWeek;

					if (!SystemTimeToFileTime(&SysTime, &FileInfo.ftLastAccessTime))
					{
						std::cout << "������ ��� ��������� ������� ���������� ������� � ����� \"" << cPath << "\"." << std::endl;
						break;
					};

					//����� ��������� ������ � ����
					std::cout << "������� ���� ��������� ������ � ����: ";
					std::cin >> SysTime.wDay;

					std::cout << "������� ����� ��������� ������ � ����: ";
					std::cin >> SysTime.wMonth;

					std::cout << "������� ��� ��������� ������ � ����: ";
					std::cin >> SysTime.wYear;

					std::cout << "������� ��� ��������� ������ � ����: ";
					std::cin >> SysTime.wHour;

					std::cout << "������� ������ ��������� ������ � ����: ";
					std::cin >> SysTime.wMinute;

					std::cout << "������� ������� ��������� ������ � ����: ";
					std::cin >> SysTime.wSecond;

					std::cout << "������� ������������ ��������� ������ � ����: ";
					std::cin >> SysTime.wMilliseconds;

					std::cout << "������� ���� ������ ��������� ������ � ����: ";
					std::cin >> SysTime.wDayOfWeek;

					if (!SystemTimeToFileTime(&SysTime, &FileInfo.ftLastWriteTime))
					{
						std::cout << "������ ��� ��������� ������� ��������� ������ � ���� \"" << cPath << "\"." << std::endl;
						break;
					};

					if (SetFileTime(hdl, &FileInfo.ftCreationTime, &FileInfo.ftLastAccessTime, &FileInfo.ftLastWriteTime))
						std::cout << "�������� ����� \"" << cPath << "\" ������� ��������." << std::endl;
					else
					{
						std::cout << "������ ��� ��������� ��������� ����� \"" << cPath << "\"." << std::endl;
						break;
					};
					

				}
				else
				{
					std::cout << "������! ����� �������� �������� ��� ������ ��������." << std::endl;
					std::cin.clear();
					std::cin.sync();
					break;
				};
			};

			break;
		case '0':
			break;
		default:
			std::cout << "������! ����� �������� �������� ��� ������ ������ ����." << std::endl;
			std::cin.clear();
			std::cin.sync();
			break;
		};

		delete[] DiskName;
		delete[] wcDiskName;
		delete[] cPath;
		delete[] mPath;
		delete[] cPath1;
		delete[] mPath1;
	};

	return 0;
};