<script setup>

</script>

<template>
  <div class="container">
    <h1>Goal Finder Dashboard</h1>
    <div class="row mt-5">
      <div class="col-sm-6 mb-3 mb-sm-0">
        <div class="card">
          <div class="card-body">
            <h5 class="card-title">Create new game</h5>
            <p class="card-text">Create a new basketball game</p>
            <router-link to="/games" class="btn btn-primary">Go to games</router-link>
          </div>
        </div>
      </div>
      <div class="col-sm-6">
        <div class="card">
          <div class="card-body">
            <h5 class="card-title">Configure device</h5>
            <p class="card-text">Configure the device settings like sounds and devices.</p>
            <router-link to="/config" class="btn btn-primary">Go to configuration</router-link>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<style scoped>

</style>