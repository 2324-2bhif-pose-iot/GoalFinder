<script setup>

</script>

<template>
  <div class="container">
    <h1>Goal Finder Dashboard</h1>
    <div class="row">
      <Card class="col-sm-6 dashboard-card">
        <template #title>Create new game</template>
        <template #content>
          <p class="m-0">
            Create a new basketball game
          </p>
          <router-link to="/games">
            <Button class="mt-3" label="Go to games"/>
          </router-link>
        </template>
      </Card>
      <Card class="col-sm-6 dashboard-card">
        <template #title>Configure device</template>
        <template #content>
          <p class="m-0">
            Configure the device settings like sounds and devices.
          </p>
          <router-link to="/settings">
            <Button class="mt-3" label="Go to settings"/>
          </router-link>
        </template>
      </Card>
      <Card class="col-sm-6 dashboard-card">
        <template #title>Basketball shot tracker</template>
        <template #content>
          <p class="m-0">
            Add and remove persons into a basketball shot tracker
          </p>
          <router-link to="/list">
            <Button class="mt-3" label="Go to Basketball shot tracker"/>
          </router-link>
        </template>
      </Card>
    </div>
  </div>
</template>

<style scoped>
</style>