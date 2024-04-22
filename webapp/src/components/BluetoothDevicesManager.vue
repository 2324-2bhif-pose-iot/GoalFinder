<script setup>
  import {ref} from "vue";
  const isEnabled = ref(false);

</script>

<template>
  <div>
    <div class="form-check form-switch mb-3">
      <input class="form-check-input" type="checkbox" role="switch" id="flexSwitchCheckDefault" v-model="isEnabled">
      <label class="form-check-label" for="flexSwitchCheckDefault">Bluetooth</label>
    </div>
    <div id="device-containers" v-show="isEnabled">
      <div class="card mb-3">
        <div class="card-header">
          Paired Devices
        </div>
        <ul class="list-group list-group-flush device-container">
          <li class="list-group-item list-group-item-action">Device 1</li>
          <li class="list-group-item list-group-item-action">An item</li>
        </ul>
      </div>
      <div class="card">
        <div class="card-header">
          Other Devices
        </div>
        <ul class="list-group list-group-flush device-container">
          <li class="list-group-item list-group-item-action">An item</li>
          <li class="list-group-item list-group-item-action">A second item</li>
          <li class="list-group-item list-group-item-action">A third item</li>
        </ul>
      </div>
    </div>
  </div>
</template>

<style scoped>
  .device-container {
    overflow-y: scroll;
    max-height: 12.7rem;
  }
</style>