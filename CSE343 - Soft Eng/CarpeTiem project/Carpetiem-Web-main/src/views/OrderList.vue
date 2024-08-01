<template>
  <div class="table-responsive" id="general_table">
    <h3 class="p-3 text-center">Tüm Siparişler Aşağıda Listelenmiştir</h3>
    <table class="table table-dark table-striped">
      <thead>
        <tr>
          <th>Müşteri İsmi</th>
          <th>Müşteri Tel_no</th>
          <th>Müşteri Email</th>
          <th>Halı Alanı</th>
          <th>Halı Fiyatı</th>
          <th>Halı Tipi</th>
          <th>Halı Durumu</th>
        </tr>
      </thead>
      <tbody>
        <tr v-for="carpet in carpets" :key="carpet">
          <td class="listElement">
            <p class="empText">{{ carpet.name }}</p>
          </td>
          <td class="listElement">
            <p class="empText">{{ carpet.phone }}</p>
          </td>
          <td class="listElement">
            <p class="empText">{{ carpet.email }}</p>
          </td>
          <td class="listElement">
            <p class="empText">{{ carpet.area }}</p>
          </td>
          <td class="listElement">
            <p class="empText">{{ carpet.cost }}</p>
          </td>
          <td class="listElement">
            <p class="empText">{{ carpet.type }}</p>
          </td>
          <td class="listElement">
            <!-- <p class="empText">{{ carpet.status }}</p> -->
            <div v-if="carpet.status == status1" class="progress">
              <div
                class="progress-bar"
                role="progressbar"
                style="width: 25%"
                aria-valuenow="0"
                aria-valuemin="0"
                aria-valuemax="100"
              >
                {{ carpet.status }}
              </div>
            </div>
            <div v-if="carpet.status == status2" class="progress">
              <div
                class="progress-bar"
                role="progressbar"
                style="width: 50%"
                aria-valuenow="0"
                aria-valuemin="0"
                aria-valuemax="100"
              >
                {{ carpet.status }}
              </div>
            </div>
            <div v-if="carpet.status == status3" class="progress">
              <div
                class="progress-bar"
                role="progressbar"
                style="width: 75%"
                aria-valuenow="0"
                aria-valuemin="0"
                aria-valuemax="100"
              >
                {{ carpet.status }}
              </div>
            </div>
            <div v-if="carpet.status == status4" class="progress">
              <div
                class="progress-bar bg-success"
                role="progressbar"
                style="width: 100%"
                aria-valuenow="0"
                aria-valuemin="0"
                aria-valuemax="100"
              >
                {{ carpet.status }}
              </div>
            </div>
          </td>
        </tr>
      </tbody>
    </table>
  </div>
</template>

<script>
import { ref } from "@vue/reactivity";
import firebase from "firebase/compat/app";
import db, { functions } from "../firebase";

export default {
  name: "OrderList",
  components: {},
  setup() {
    const customers = ref([]);
    const carpets = ref([]);
    const status1 = ref("Alındı");
    const status2 = ref("Yıkanıyor");
    const status3 = ref("Kuruyor");
    const status4 = ref("Getiriliyor");

    db.collection("carpets")
      .get()
      .then((snap) => {
        snap.forEach((doc) => {
          var tempdata = doc.data();

          var returned;
          //Customer ID sini al ve bilgilerini getir
          try {
            var getUser = functions.httpsCallable("getUser");

            getUser({ id: tempdata.customer_id, collection: "customers" }).then(
              (result) => {
                var sanitizedMessage = result.data;
                returned = result.data;
                //console.log(result.data);
                //console.log(result.data.name);
                tempdata.name = result.data.name;
                tempdata.phone = result.data.phone;
                tempdata.email = result.data.email;
                carpets.value.push(tempdata);
              }
            );
          } catch (err) {
            console.log(err.message);
          }
          /*
          tempdata.name = "result.data.name";
          tempdata.phone = "result.data.phone";
          tempdata.email = "result.data.email";*/

          /*tempdata.name = returned.name;
          tempdata.phone = returned.phone;
          tempdata.email = returned.email;*/
        });
        carpets.value.sort(new Intl.Collator("de").compare);
      });
    return {
      customers,
      carpets,
      status1,
      status2,
      status3,
      status4,
    };
  },
};
</script>

<style scoped>
#general_table {
  margin: 2em;
}
table {
  min-height: 5vh;
  max-width: 100vw;
}
#addbtn {
  background: seagreen;

  max-width: 6em;
  min-width: 6em;
  border: 3px solid green;
  padding: 0em;
}
#rmwbtn {
  background: red;
  margin: 0.1em;
  max-width: 6em;
  min-width: 6em;
}
#edtbtn {
  background: orange;
  margin: 0.1em;
  max-width: 6em;
  min-width: 6em;
}
</style>
