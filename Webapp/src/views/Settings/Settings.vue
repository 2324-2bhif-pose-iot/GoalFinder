<script setup>
import WifiIcon from "@/components/Icons/WifiIcon.vue";
import SettingsIcon from "@/components/Icons/SettingsIcon.vue";
import BluetoothIcon from "@/components/Icons/BluetoothIcon.vue";
import VolumeIcon from "@/components/Icons/VolumeIcon.vue";
import InfoIcon from "@/components/Icons/InfoIcon.vue";
</script>

<template>
  <div class="container">
    <h1>Settings</h1>
    <div class="row mt-5">
      <div class="col-md-3 mb-3">
        <ul class="list-group">
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
        </ul>
      </div>
      <router-view class="col-md"/>
    </div>
  </div>
</template>

<style scoped>
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