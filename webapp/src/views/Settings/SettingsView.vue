<script setup>
import WifiIcon from "@/components/Icons/WifiIcon.vue";
import SettingsIcon from "@/components/Icons/SettingsIcon.vue";
import BluetoothIcon from "@/components/Icons/BluetoothIcon.vue";
import VolumeIcon from "@/components/Icons/VolumeIcon.vue";
import InfoIcon from "@/components/Icons/InfoIcon.vue";
import router from "@/router/index.js";

const options = [
  {
    label: "General",
    command: () => router.push("/settings/general")
  },
  {
    label: "Connectivity",
    command: () => router.push("/settings/connectivity")
  },
  {
    label: "Devices",
    command: () => router.push("/settings/devices")
  },
  {
    label: "Audio",
    command: () => router.push("/settings/audio")
  },
  {
    label: "System",
    command: () => router.push("/settings/system")
  },
]
</script>

<template>
  <div class="container">
    <div id="top-menu">
      <h1>Settings</h1>
      <Button label="Save settings"/>
    </div>
    <div class="row mt-5">
      <div class="col-md-3 mb-3">
        <Menu class="p-1" :model="options"/>

        <!-- <ul class="list-group">
          <router-link class="list-group-item list-group-item-action settings-item" to="/settings/general">
            <SettingsIcon/>
            General
          </router-link>
          <router-link class="list-group-item list-group-item-action settings-item" to="/settings/connectivity">
            <WifiIcon/>
            Connectivity
          </router-link>
          <router-link class="list-group-item list-group-item-action settings-item" to="/settings/devices">
            <BluetoothIcon/>
            Devices
          </router-link>
          <router-link class="list-group-item list-group-item-action settings-item" to="/settings/audio">
            <VolumeIcon/>
            Audio
          </router-link>
          <router-link class="list-group-item list-group-item-action settings-item" to="/settings/system">
            <InfoIcon/>
            System
          </router-link>
        </ul> -->
      </div>
      <router-view class="col-md"/>
    </div>
  </div>
</template>

<style scoped>

  #top-menu {
    display: flex;
    flex-wrap: wrap;
    align-items: center;
  }

  #top-menu Button {
    margin-left: auto;
  }

  .settings-item {
    display: flex;
    align-items: center;
    gap: 0.6rem;
  }

  .settings-item svg {
    width: 1.15rem;
    height: 1.15rem;
    margin-top: 0.1rem;
  }
</style>