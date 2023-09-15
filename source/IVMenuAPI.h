namespace IVMenuAPI
{
	bool IsSupported()
	{
		if (GetModuleHandleA("IVMenuAPI.asi")) return 1;

		static bool bTriedToLoad = 0;
		if (!bTriedToLoad && LoadLibraryA("IVMenuAPI.asi")) return 1;
		bTriedToLoad = 1;
		return 0;
	}

	void AddMenuOption(const char* nameId, void* callbackData, int32_t(*GetValue)(void*), void(*SetValue)(void*, int32_t))
	{
		auto inst = GetModuleHandleA("IVMenuAPI.asi");
		if (!inst) return;

		if (auto addr = (uintptr_t)GetProcAddress(inst, "AddIVMenuOption"))
		{
			return ((void(__cdecl*)(const char*, int, int, int, int, void*, int32_t(*)(void*), void(*)(void*, int32_t)))addr)(nameId, 0, 0, 0, 0, callbackData, GetValue, SetValue);
		}
	}

	void AddMenuEnum(const char* nameId)
	{
		auto inst = GetModuleHandleA("IVMenuAPI.asi");
		if (!inst) return;

		if (auto addr = (uintptr_t)GetProcAddress(inst, "AddIVMenuEnum"))
		{
			return ((void(__cdecl*)(const char*, int, int, int))addr)(nameId, 0, 0, 0);
		}
	}
}