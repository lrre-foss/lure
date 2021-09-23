# RbxHooks
Easy to use client modifications for old Roblox 

## Hooks
These describe the included hooks with RbxHooks, but you can also add your own! RbxHooks provides a very easy format to adding your own hooks.

- TrustCheck: Basic hook that detours the internal Roblox IsTrustedSite function and replaces it with a custom one.
- SwapIp: Censors all peer IPs in a NetworkServer by displaying them as "RakPeer".

## Usage
For finding hook addresses, [x64dbg](https://x64dbg.com/) is recommended. For patching the import table, [StudPE](http://www.cgsoftlabs.ro/studpe.html) is recommended.

1. Compile RbxHooks as **x86**, and copy the output DLL file to the folder where you are keeping `RobloxApp.exe`.
1. Open `RobloxApp.exe` with StudPE (File -> Open PE File)
2. Go to the **Functions** tab
3. Right click in the left panel and click **Add New Import**.
4. Click **Dll Select** and browse to `RbxHooks.dll` in your Blockland folder.
5. Click **Select func.** and select `patch` from the list that appears.
6. Click `Add to list`, then `ADD` at the bottom.
7. Close the program by clicking `OK`. This will also save the patches to the executable file.

## License
RbxHooks is licensed under the MIT license. A copy of the license [has been included](https://github.com/orcfoss/RbxHooks/blob/trunk/LICENSE) with RbxHooks.